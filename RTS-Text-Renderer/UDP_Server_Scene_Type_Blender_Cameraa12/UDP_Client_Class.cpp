#include "UDP_Client_Class.h"


#include "common_multiplayer5.h" // Your common header
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>

// Winsock Libraries for Windows Networking
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "PacketToSend_queue.h"

// https://beej.us/guide/bgnet/html/split/ip-addresses-structs-and-data-munging.html

// https://github.com/ioan45/rts-multiplayer-game

// https://github.com/ExtraSoupGames/UDPGameNetworking/blob/main/UDPGameNetworking/NetworkObjects/NetworkObject.cpp
// https://github.com/FutureXXH/UDPGAMESERVER/blob/main/IOCPSERVER.cpp
// https://github.com/Physical-Intelligence/openpi Phyiscally intelligent H100 A100 Nvidia

//https://www.reddit.com/r/RealTimeStrategy/wiki/recommended/

int g_iMyUserIDClientID = 0;

#ifdef _WIN32
void set_dscp(SOCKET sockfd, int dscp_value);
#else
void set_dscp(int sockfd, int dscp_value);
#endif

bool winsock_init()
{

	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
		std::cerr << "WSAStartup failed." << std::endl;
		return 0;
	}
	printf("winsock_init Initialised.\n");

	return 1;

}
// https://web.stanford.edu/class/archive/cs/cs107/cs107.1238/lectures/20/quickref.html
// https://disi.unitn.it/~guna/teach/sockets.pdf

//const char* pkt = "Message to be sent";
#define BUFFERLENGTH 100
int BufLength = BUFFERLENGTH;
char* SendBuf[BUFFERLENGTH];
//const char* srcIP = "";
char szSRC_IP[65];

const char* destIP = "192.168.0.223";

const char* destIP2 = "192.168.0.155";

//sockaddr_in dest;
//sockaddr_in local;

struct sockaddr_in si_other;
int s, slen = sizeof(si_other);


uint32_t PORT = 9080;
uint32_t uiRequestID = 0;
uint32_t uiThreadLoopNum = 0;
uint32_t uiConnected = 0;
//bool bIsClientLoopUDPRunning = false;
// Shared data and synchronization for the new thread
//std::vector<Cube> cubes;
#include "UDPClient_update-AABB-Cubes.h"     // to include extern std::vector<Cube> cubes;
std::mutex cubes_mutex;
std::atomic<bool> bIsClientLoopUDPRunning(true);
void udp_receive_thread(SOCKET sock);

void* udp_sending_test_thread(void* arg); // deplicate, refactor 9/19/2025

uint32_t sequence_buffer[BufferSize];

PacketData packet_data[BufferSize];

bool is_sending_thread_running = false; //refactor to std::amotic<bool> ?

PacketData* GetPacketData(uint16_t sequence)
{
	const int index = sequence % BufferSize;
	if (sequence_buffer[index] == sequence)
		return &packet_data[index];
	else
		return NULL;
}

bool winsock_connect()
{
	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	// Note: https://www.youtube.com/watch?v=S9eRizbjUtE 
	// Might Work for consumer rounter, maybe help someone
	// Set DSCP to a high-priority value (e.g., EF - Expedited Forwarding, decimal 46)
	// You can also use CS5 (Control Systems, decimal 40) or others.
	const int DSCP_EF = 46;
	set_dscp(s, DSCP_EF);

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	//si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
	// 'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
//	si_other.sin_addr.S_un.S_addr = inet_addr(destIP);
	//inet_pton(AF_INET, SERVER_V3000_DEV_IP, &server_addr.sin_addr);
	// inet_pton(AF_INET, destIP2, &si_other.sin_addr);
	inet_pton(AF_INET, destIP2, &si_other.sin_addr);


	JoinRequestCommand cmd;
	//	cmd.uiRequestID = client_id;
	//	cmd.uiThreadLoopNum = object_id;
	//	cmd.uiConnected = { x, y, z };
		/*
		struct JoinRequestCommand {
		uint32_t uiRequestID;
		uint32_t uiThreadLoopNum;
		uint32_t uiConnected;
		char szCRC64Code[64]; // new for Salt for Verify Game Client

	};
	*/
	cmd.uiRequestID = uiRequestID;
	cmd.uiThreadLoopNum = uiThreadLoopNum;
	cmd.uiConnected = uiConnected;
	// sprintf(cmd.szCRC64Code, "%s", "FEWOkf233F#@OKF#@OKf#FO#@kfk3okfl;k3f32wjf32kjf32k3j2foi3fo3jf3f");// our temp password
	sprintf_s(cmd.szCRC64Code, "%s", "FEWOkf233F#@OKF#@OKf#FO#@kfk3okfl;k3f32wjf32kjf32k3j2foi3fo3jf3f");// our temp password


	MessageHeader header;
	header.type = JOIN_REQUEST;
	header.size = sizeof(JoinRequestCommand);

	//send_message_udp2(header, (const char*)&cmd);
	//bool send_message_udp2(const MessageHeader & header, const char* data) {
		// Send header and data in a single packet to minimize overhead
	std::vector<char> packet_buffer(sizeof(MessageHeader) + header.size);
	memcpy(packet_buffer.data(), &header, sizeof(MessageHeader));
	if (header.size > 0) {
		memcpy(packet_buffer.data() + sizeof(MessageHeader), (const void*)&cmd, header.size);
	}

	if (sendto(s, packet_buffer.data(), packet_buffer.size(), 0, (sockaddr*)&si_other, slen) == SOCKET_ERROR) {
		std::cout << "sendto failed: " << WSAGetLastError() << std::endl;
		return false;
	}

	// Set a receive timeout to prevent blocking indefinitely
//	DWORD timeout = 100; // 100ms
			////	if (setsockopt(client_socket_udp, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) == SOCKET_ERROR) {
//	if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) == SOCKET_ERROR) {
//		std::cerr << "setsockopt failed: " << WSAGetLastError() << std::endl;
//	}

#define MAX_UDP_PACKET_SIZE2 101
	char sz_packet_buffer[MAX_UDP_PACKET_SIZE2];
	//	sockaddr_in sender_addr;
	//	int sender_addr_size = sizeof(sender_addr);
		//  int iPacketGetSize = 512;
	int iPacketGetSize = 100;
	//int bytes_received = recvfrom(client_socket_udp, packet_buffer, sizeof(packet_buffer), 0, (sockaddr*)&sender_addr, &sender_addr_size);
	//   int bytes_received = recvfrom(client_socket_udp, packet_buffer, iPacketGetSize, 0, (sockaddr*)&sender_addr, &sender_addr_size);
//	int bytes_received = recvfrom(s, sz_packet_buffer, sizeof(sz_packet_buffer), 0, (sockaddr*)&sender_addr, &sender_addr_size);
	// https://stackoverflow.com/questions/679145/how-to-set-up-a-winsock-udp-socket
	int bytes_received = recvfrom(s, sz_packet_buffer, sizeof(sz_packet_buffer), 0, (sockaddr*)&si_other, &slen);

	if (bytes_received == SOCKET_ERROR) {
		// Handle timeout and other errors
		return false;
	}

	// Check if the received packet is from our server
	// For a simple client, we assume all packets are from the server

	// Deserialize header
	memcpy(&header, sz_packet_buffer, sizeof(MessageHeader));
	// https://www.gabrielgambetta.com/client-server-game-architecture.html
	// https://kinematicsoup.com/news/2019/9/8/the-economics-of-web-based-multiplayer-games?s=gd
	// 
	// https://www.reddit.com/r/gamedev/comments/uo2z6h/recommended_books_to_read_for_multiplayer/
	// 
	// Check for buffer overflow
	if (sizeof(MessageHeader) + header.size > bytes_received) {
		std::cout << "Received corrupted packet. Header size mismatch. 1" << std::endl;
		std::cout << "header.type:" << header.type << std::endl;
		std::cout << "header.size:" << header.size << std::endl;
		return false;
	}
	if (header.size < 101)
	{
		//	char data[100];
		char* data = NULL;


		// Deserialize data payload
		if (data) delete[] data;
		if (header.size > 0 && header.size < 101) {
			data = new char[header.size];
			memcpy(data, sz_packet_buffer + sizeof(MessageHeader), header.size);

			JoinRequestCommand cmdBack;
			memcpy((void*)&cmdBack, data, header.size);
			printf("cmdBack:\n");
			printf("cmdBack.uiConnected:%d\n", cmdBack.uiConnected);
			printf("cmdBack.uiRequestID:%d\n", cmdBack.uiRequestID);
			printf("cmdBack.uiThreadLoopNum:%d\n", cmdBack.uiThreadLoopNum);
			printf("cmdBack.szCRC64Code:%s\n", cmdBack.szCRC64Code);          // Compare if our message is Welcome to Alliance & Allegence
			if (strstr(cmdBack.szCRC64Code, "Welcome to Alliance & Allegence") != NULL)
			{
				uiRequestID = cmdBack.uiRequestID;

				printf("successfully Connected To  Alliance & Allegence \n");

				printf("ClientID: %d\n", uiRequestID);
				g_iMyUserIDClientID = uiRequestID;
				uiRequestID = 2;
				return true;
			}
		}
		else {
			data = nullptr;
		}

	}


	return true;
	//return false;
	//}


	//if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	//if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
	//{
	//	printf("sendto() failed with error code : %d", WSAGetLastError());
	//	exit(EXIT_FAILURE);
	//}



}

int UDP_Client_Class_Connect()
{
	int iWinSock_Init = winsock_init();
	if (!iWinSock_Init)
	{
		return 0;

	}
	bool bConnect = winsock_connect();
	if (!bConnect)
	{
		return 0;

	}

	// Create a new thread to handle incoming game state packets
	std::thread receive_thread(udp_receive_thread, (SOCKET)s);
	receive_thread.detach(); // Detach the thread so it runs independently

	//	std::thread send_test_thread(udp_sending_test_thread, (void*)s);
	//	send_test_thread.detach(); // Detach the thread so it runs independently

	std::thread SendPacketInQue(SendPacketInQue_queue, (void*)s);
	SendPacketInQue.detach(); // Detach the thread so it runs independently

	is_sending_thread_running = true;

	return 1;
}

int  GetClientID()
{
	return uiRequestID;

}

bool send_message_udp_queue(const MessageHeader& header, const char* data) {
	// Send header and data in a single packet to minimize overhead
	std::vector<char> packet_buffer(sizeof(MessageHeader) + header.size);
	memcpy(packet_buffer.data(), &header, sizeof(MessageHeader));
	if (header.size > 0) {
		memcpy(packet_buffer.data() + sizeof(MessageHeader), data, header.size);
	}

	//if (sendto(client_socket_udp, packet_buffer.data(), packet_buffer.size(), 0, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
	if (sendto(s, packet_buffer.data(), packet_buffer.size(), 0, (sockaddr*)&si_other, slen) == SOCKET_ERROR) {
		std::cout << "sendto failed: " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}
#ifdef _WIN32
// The function signature remains the same, but the implementation changes.

// https://www.youtube.com/watch?v=bcEl6VRnURk Manualy way to set policy QoS

void set_dscp(SOCKET sockfd, int dscp_value) {
	int tos = dscp_value << 2; // DSCP is the top 6 bits of the TOS/DS field

	// The key change is here: cast the int pointer to a const char*
	if (setsockopt(sockfd, IPPROTO_IP, IP_TOS, (const char*)&tos, sizeof(tos)) == SOCKET_ERROR) {
		// Use WSAGetLastError() for Winsock errors
		std::cerr << "setsockopt failed with error code: " << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "DSCP value " << dscp_value << " set successfully." << std::endl;
	}
}

#else
void set_dscp(int sockfd, int dscp_value) {
	int tos = dscp_value << 2; // DSCP is the top 6 bits of the TOS/DS field
	if (setsockopt(sockfd, IPPROTO_IP, IP_TOS, &tos, sizeof(tos)) < 0) {
		perror("setsockopt failed");
	}
	else {
		std::cout << "DSCP value " << dscp_value << " set successfully." << std::endl;
	}
}
#endif

void SendPacketInQue(SOCKET sock)
{

	std::cout << "SendPacketInQue(SOCKET sock) " << sock << " set successfully." << std::endl;

}
void 	AddCubeNetwork(Cube received_cube)
{

	int iIndexVertices = AddCubeNetworked(received_cube);

}

// https://gemini.google.com/u/1/app/ee29a22edf43cb19


// Thread function for receiving game state packets
void udp_receive_thread(SOCKET sock) {
	char sz_packet_buffer[101];
	int iPacketGetSize = 100;
	sockaddr_in sender_addr;
	socklen_t sender_addr_size = sizeof(sender_addr);

	while (bIsClientLoopUDPRunning) {
		int bytes_received = recvfrom(sock, sz_packet_buffer, sizeof(sz_packet_buffer), 0, (sockaddr*)&sender_addr, &sender_addr_size);

		if (bytes_received == SOCKET_ERROR) {
			int error = WSAGetLastError();
			if (error == WSAETIMEDOUT) {
				continue; // No data, just continue the loop
			}
			std::cout << "recvfrom failed with error: " << error << std::endl;
			//bIsClientLoopUDPRunning = false;
			continue;
		}

		// SequenceID increament
		uiRequestID++; // requestID is sequence packet number

		MessageHeader header;
		memcpy(&header, sz_packet_buffer, sizeof(MessageHeader));

		if (sizeof(MessageHeader) + header.size > bytes_received) {
			std::cout << "Received corrupted packet. Header size mismatch. 2" << std::endl;
			std::cout << "header.type:" << header.type << std::endl;
			std::cout << "header.size:" << header.size << std::endl;

			continue;
		}

		switch (header.type) {
		case GAME_STATE: {
			if (header.size == sizeof(Cube)) {
				Cube received_cube;
				memcpy(&received_cube, sz_packet_buffer + sizeof(MessageHeader), sizeof(Cube));

				// Use a mutex to protect the shared vector
				std::lock_guard<std::mutex> lock(cubes_mutex);
				//	cubes.push_back(received_cube); // bad, will crash and not have graphics data cubeGraphicsData
					// also not being sent to GPU
					// maybe make  a que so its on anouther thread being sent to GPU
					//-----------------____________________________+++++++++++++++++++++++++++
				AddCubeNetwork(received_cube);

				// KEY AREA FOR ADDING A THREAD FOR UPADING GPU GRAPHICS , CONCURRENT TO 
				//RUNNING MAIN LOOP
				//
				// 
				//                            |---------| 
				//                            |Draw Loop|
				//                            |_________|
				//                              |
				//                              |
				// /--------------=|------------|  ____________________
				// |Main Thread    |---------------| GPU UPDATER THREAD|
				// ________________|---------|      --------------------                -______________________________
				//                           |                                          |                              |
				//                           |-----------------------------------------+| Backup Client Physics thread |
				//                           |                                          |______________________________|
				//                        -------------------
				//                        | Network Thread  |
				//                        -------------------
				// 
				// 				//        ---------------------------------
				//                        | CURL Thread Game Coordinator  |
				//                        ---------------------------------
				// 
				// 
				// 
				//                        ---------------------------------
				//                        | Input Thread                  |
				//                        ---------------------------------
				// 
				// 			//            ---------------------------------
				//                        | Image Generator Thread Game   |
				//                        ---------------------------------
				// 
				// 
				// 	// 
				// 			//            ---------------------------------
				//                        | Shader Compiler Thread Game   |
				//                        ---------------------------------
				// 
				// // 			          ---------------------------------|
				//                        | Asset Import Loader Thread Game|
				//                        ---------------------------------|
				// 
				//-----------------____________________________+++++++++++++++++++++++++++

				std::cout << "Received Cube: (id=" << received_cube.id << ", x=" << received_cube.position.x << ", y=" << received_cube.position.y << ", z=" << received_cube.position.z << ")" << std::endl;
			}
			break;
		}
		case ERROR_MESSAGE:
			std::cout << "Received an error message from the server." << std::endl;
			break;
		default:
			// Handle other message types if necessary
			break;
		}


		// send something?
		SendPacketInQue(sock);


	}
	std::cout << "Receive thread shutting down." << std::endl;
}

#include <queue>
// Thread-safe queue for outgoing packets
std::queue<PacketToSend> packet_queue;
std::mutex queue_mutex;
std::condition_variable outgoing_cv;

// New thread function for sending packets from the queue
void SendPacketInQue_queue(void* sock2)
{
	SOCKET sock = (SOCKET)sock2;

	std::cout << "SendPacketInQue(SOCKET sock) thread started." << std::endl;

	while (is_sending_thread_running)
	{
		PacketToSend packet;
		bool packet_found = false;

		// Lock the mutex to safely access the queue
		{
			std::lock_guard<std::mutex> lock(queue_mutex);
			if (!packet_queue.empty()) {
				packet = packet_queue.front();
				packet_queue.pop();
				packet_found = true;
			}
		} // Mutex is released here

		if (packet_found) {
			// Construct the full packet buffer for sending
			std::vector<char> packet_buffer(sizeof(MessageHeader) + packet.data.size());
			memcpy(packet_buffer.data(), &packet.header, sizeof(MessageHeader));
			if (!packet.data.empty()) {
				memcpy(packet_buffer.data() + sizeof(MessageHeader), packet.data.data(), packet.data.size());
			}

			// Send the packet over the network
			if (sendto(sock, packet_buffer.data(), packet_buffer.size(), 0, (sockaddr*)&si_other, slen) == SOCKET_ERROR) {
				std::cout << "sendto failed: " << WSAGetLastError() << std::endl;
			}
		}
		else {
			// No packets to send, so sleep for a short duration to avoid a busy-wait loop
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	std::cout << "Send thread shutting down." << std::endl;
}

// This function now just adds the packet to the thread-safe queue
bool send_message_udp_queue_queue(const MessageHeader& header, const char* data) {
	// Send header and data in a single packet to minimize overhead
	PacketToSend new_packet;
	new_packet.header = header;
	if (header.size > 0) {
		new_packet.data.assign(data, data + header.size);
	}

	// Use a lock to safely push the packet onto the queue
	std::lock_guard<std::mutex> lock(queue_mutex);
	packet_queue.push(new_packet);

	return true;
}

// https://gemini.google.com/app/5b09925ae01939bc tickRate prompt
long int client_info_tickRate = 50; // 50 millisecond update send packet
// see code above for the real queue pack approach
void* udp_sending_test_thread(void* arg)
{
	bool isClientLoopRunning = true;


	while (isClientLoopRunning)
	{

		int client_id_udp = GetClientID(); // move this to a GameCoordinator Class, and a API AllainceAndAllegenceID class
		int selected_cube_id_udp = 1; // fix the raytrace detection, by adding to more objects

		int client_id = client_id_udp; // GetClientID, flag_COMMAND_REFRESH_UDP_ID
		int object_id = selected_cube_id_udp; // selected_cube_client_id, selected_cube_server_id
		std::cout << "Error: Get clientid from server:" << std::endl;
		std::cout << "Error: Get objectid from server/client?:" << std::endl;

		//	MoveCommand cmd;
		//	cmd.player_id = client_id;
		//	cmd.object_id = object_id;
		//	cmd.destination = { x, y, z };

		MessageHeader header;
		header.type = GAME_STATE;
		//header.size = sizeof(MoveCommand);
		header.size = sizeof(Cube);

		//	Cube cmd;
		//	cmd.position.x = cubes[i].position.x;
		//	cmd.position.y = cubes[i].position.y;
		//	cmd.position.z = cubes[i].position.z;

		//	cmd.velocity.x = cubes[i].velocity.x;
		//	cmd.velocity.y = cubes[i].velocity.y;
		//	cmd.velocity.z = cubes[i].velocity.z;

		//	cmd.halfSize = cubes[i].halfSize;
		//	cmd.iRenderType = cubes[i].iRenderType;
		//	cmd.iHighLight[0] = cubes[i].iHighLight[0];
		//	cmd.iHighLight[1] = cubes[i].iHighLight[1];
		//	cmd.iHighLight[2] = cubes[i].iHighLight[2];
		//	cmd.iHighLight[3] = cubes[i].iHighLight[3];

		//	cmd.owner_id = cubes[i].owner_id;
		//	cmd.id = cubes[i].id;


		Cube cmd;
		cmd.position.x = 5.0f;
		cmd.position.y = 5.0f;
		cmd.position.z = 1.0f;

		cmd.velocity.x = 0.0f;
		cmd.velocity.y = 0.0f;
		cmd.velocity.z = 0.0f;

		cmd.halfSize = 0.5f;
		cmd.iRenderType = 1;
		cmd.iHighLight[0] = 33;
		cmd.iHighLight[1] = 34;
		cmd.iHighLight[2] = 35;
		cmd.iHighLight[3] = 36;

		cmd.owner_id = GetClientID();
		cmd.id = cubes.size();



		send_message_udp_queue(header, (const char*)&cmd);
		//std::this_thread::sleep_for(std::chrono::milliseconds((long int)client_info->tickRate));

		std::this_thread::sleep_for(std::chrono::milliseconds(client_info_tickRate));
	}


	return NULL;

}
