
#include "common_multiplayer4.h"


        // #include "glm/glm.hpp"
        // #include "glm/gtx/norm.hpp"

        #include "rts_udp_game_server.h"

        // --- Global Data and Constants ---
        const int PORT = 9080;
        const int TICK_RATE = 60; // 60 ticks per second
        const std::chrono::milliseconds TICK_DURATION(1000 / TICK_RATE);
        const float GRAVITY = -9.8f;


        int next_player_id = 1;


        std::vector <Cube> cubes;

int main(int argc, char **argv)
{
        printf("Starting V3000 RTS Server Engine 0.3v\n");
        initCubes();
        socket_linux_connect_clients();

        return 0;

}

        bool socket_linux_connect_clients()
        {
           int server_socket_fd;
          //  struct sockaddr_in address;
           struct sockaddr_in server_address;

                // Zero out the server address structure
                memset(&server_address, 0, sizeof(server_address));


                // Create a UDP datagram socket
                if ((server_socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
                        perror("socket failed");
                        exit(EXIT_FAILURE);
                }

                // Forcefully attach socket to the port 8080
                int opt = 1;
                if (setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
                        perror("setsockopt");
                        exit(EXIT_FAILURE);
                }

                server_address.sin_family = AF_INET;
                server_address.sin_addr.s_addr = INADDR_ANY;
                server_address.sin_port = htons(PORT);

                // Bind the socket to the address and port
                if (bind(server_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
                        perror("bind failed");
                        exit(EXIT_FAILURE);
                }

                std::cout << "UDP Server listening on port " << PORT << std::endl;
                ServerInfo * server_info  = new ServerInfo;
                                        server_info->server_socket_fd = server_socket_fd;
                                        server_info->server_address = server_address;
                                        server_info->iServerID = 1; // Get from TCP Server
                                        server_info->LastTimeGotPacket = 0;       // for timeout disconnect;//
                                                        // To set a 10 Hz tick rate in milliseconds, you need to calculate the duration of a single tick.
                                                        // A frequency of 10 Hz means 10 cycles per second. To find the duration of one cycle in milliseconds, you can use the following formula:
                                                        // Tick Duration (ms) = 1000 ms / Tick Rate (Hz)
                                                        // Tick Duration (ms) = 1000 / 10
                                                        // Tick Duration (ms) = 100
                                                        // Therefore, a 10 Hz tick rate corresponds to a tick duration of 100 milliseconds.
                                                        // In floating-point milliseconds, this would simply be 100.0f.
                                        //client_info->tickRate = 2.0f; // 2 milli seconds                   // custom rate for rate client get sent things
                                        server_info->tickRate = 100.0f;

                pthread_t thread_id_server;
                                        if (pthread_create(&thread_id_server, NULL, udp_server_receive_only_thread, (void*)server_info) != 0) {
                                                perror("pthread_create failed");
                                                delete server_info; // Clean up memory if thread creation fails
                                        } else {
                                                // Store the new thread ID in our map

                                        //      serverinfos.push_back(server_info);

                                        //      connected_clients[client_key] = thread_id;
                                                pthread_detach(thread_id_server); // Detach the thread so we don't need to join it later
                                                printf("Created pthread udp_server_receive_only_thread thread_id_server: %d", thread_id_server);
                                        }

                                        bool bServerRunning = true;

                                        while(bServerRunning)
                                        {

                                        }

          //  close(sockfd);

                return 0;

        }




void * udp_server_receive_only_thread (void* arg)
// void* handle_client(void* arg)
//switch client.id
 //   recvfrom

 {

         // 1. Cast the void* argument back to our struct type.
                ServerInfo* server_info = static_cast<ServerInfo*>(arg);

                // 2. IMPORTANT: Copy the data to the thread's own stack and free the heap memory.
                // This prevents memory leaks and ensures the main thread doesn't have to worry
                // about the lifetime of the pointer it passed.
                int server_socket_fd = server_info->server_socket_fd; // already binded, kinda connected socket from main thread..
                struct sockaddr_in server_addr = server_info->server_address;
                //socklen_t slen = sizeof(client_addr);


         struct sockaddr_in client_address;
         memset(&client_address, 0, sizeof(client_address));

                bool isServerRunning = true;

                        //keep listening for data
                while(isServerRunning)
                {
                #define MAX_UDP_PACKET_SIZE2 101
                        char buf[MAX_UDP_PACKET_SIZE2];

                //struct sockaddr_in si_other;
                //int s,
           // int slen = sizeof(si_other);
          // socklen_t slen = sizeof(si_other); // Initialize with the size of the address structure
                socklen_t slen = sizeof(client_address);

                        printf("Waiting for data...");
                        fflush(stdout);
                        int recv_len= 0;
                        #define BUFLEN 100
                        //try to receive some data, this is a blocking call
                        if ((recv_len = recvfrom(server_socket_fd, buf, BUFLEN, 0, (struct sockaddr *) &client_address, &slen)) == -1)
                        {
                                printf("recvfrom()");
                        }

                        //print details of the client/peer and the data received
                        printf("Received packet from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
                        printf("Data: %s\n" , buf);
                        MessageHeader header;
                        memcpy(&header, buf, sizeof(MessageHeader));

                        printf("Got Packet: \n");
                        printf("header.type: %d\n",header.type);
                        printf("header.size: %d\n", header.size);

                        switch (header.type) {
           //     case ' ': break;
                        case JOIN_REQUEST: {
                        //    later add a thread created somewhere here for the client, can try to open anoouther port that
                        // client will connect to.

                                if (header.size < 101)
                                {
                                //      char data[100];
                                        char *data = NULL;


                                // Deserialize data payload
                                if (data) delete[] data;
                                if (header.size > 0) {
                                        data = new char[header.size];
                                        memcpy(data, buf + sizeof(MessageHeader), header.size);

                                        JoinRequestCommand cmdBack;
                                        memcpy((void*)&cmdBack, data, header.size);
                                        printf("cmdBack:\n");
                                        printf("cmdBack.uiConnected:%d\n", cmdBack.uiConnected);
                                        printf("cmdBack.uiRequestID:%d\n", cmdBack.uiRequestID);
                                        printf("cmdBack.uiThreadLoopNum:%d\n", cmdBack.uiThreadLoopNum);
                                        printf("cmdBack.szCRC64Code:%s\n", cmdBack.szCRC64Code);          // Compare if our message is Welcome to Alliance & Allegence
                                        if(strstr(cmdBack.szCRC64Code, "FEWOkf233F#@OKF#@OKf#FO#@kfk3okfl;k3f32wjf32kjf32k3j2foi3fo3jf3f" ) != NULL)
                                        {

                                          int  uiRequestID = cmdBack.uiRequestID;

                                                printf("successfully Connected To  Alliance & Allegence \n");

                                                printf("ClientID: %d\n", uiRequestID);

        // add new player

        // Get client IP and port to create a unique identifier
                        char client_ip[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
                        int client_port = ntohs(client_address.sin_port);
                        std::string client_key = std::string(client_ip) + ":" + std::to_string(client_port);

                        std::lock_guard<std::mutex> lock(server_info->clients_mutex); // Lock the map for safe access

                                // Check if we already have a thread for this client
                                if (server_info->connected_clients.find(client_key) == server_info->connected_clients.end()) {
                                        std::cout << "[Main Thread] New client joined. Creating a dedicated thread..." << std::endl;

                                        // Dynamically allocate ClientInfo to pass to the thread
                                        //ClientInfo* client_info = new ClientInfo;
                                        std::unique_ptr<ClientInfo> client_info = std::make_unique<ClientInfo>();


                                        client_info->server_socket_fd = server_socket_fd;
                                        client_info->client_address = client_address;
                                        client_info->iPlayerID = next_player_id;
                                        client_info->LastTimeGotPacket = 0;       // for timeout disconnect;//
                                                        // To set a 10 Hz tick rate in milliseconds, you need to calculate the duration of a single tick.
                                                        // A frequency of 10 Hz means 10 cycles per second. To find the duration of one cycle in milliseconds, you can use the following formula:
                                                        // Tick Duration (ms) = 1000 ms / Tick Rate (Hz)
                                                        // Tick Duration (ms) = 1000 / 10
                                                        // Tick Duration (ms) = 100
                                                        // Therefore, a 10 Hz tick rate corresponds to a tick duration of 100 milliseconds.
                                                        // In floating-point milliseconds, this would simply be 100.0f.
                                        //client_info->tickRate = 2.0f; // 2 milli seconds                   // custom rate for rate client get sent things
                                        client_info->tickRate = 100.0f; // 2 milli seconds                   // custom rate for rate client get sent things
                                        client_info->iNumAuthGot= 0;  // so that don't have to sendto in recvfrom only loop, need this variable to authenticate, then reauthenticate players
                                        client_info->iNumAuthGot++; // got a client trying to authenticate, later if client disconnected or reloaded, or crashed, or restarted the game, this will reconnect. readd a thread for player,
                                                // or recycle thread.
                                        server_info->clientinfos.push_back(std::move(client_info));

                                        pthread_t thread_id;
                                        //if (pthread_create(&thread_id, NULL, udp_server_sendto_particular_client, (void*)server_info->clientinfos[server_info->clientinfos.size() -1]) != 0) {
                                                if (pthread_create(&thread_id, NULL, udp_server_sendto_particular_client, server_info->clientinfos.back().get()) != 0) {
                                                perror("pthread_create failed");
                                        //      delete client_info; // Clean up memory if thread creation fails
                                            server_info->clientinfos.pop_back();        // Don't call delete. The unique_ptr in the vector will clean up.
                                                // If the thread creation fails, you might want to remove the element from the vector:


                                        } else {
                                                // Store the new thread ID in our map

                                                //server_info->clientinfos.push_back(client_info);
                                                //server_info->clientinfos.push_back(*client_info);
                                        //      server_info->clientinfos.push_back(std::unique_ptr<ClientInfo>(client_info));



                                                server_info->connected_clients[client_key] = thread_id;
                                                pthread_detach(thread_id); // Detach the thread so we don't need to join it later
                                        }
                                } else {
                                        std::cout << "[Main Thread] This client has already joined. Ignoring JOIN request." << std::endl;
                                }




                                                                next_player_id++;
                                        //    return true;
                                        }
                                }
                                else {
                                        data = nullptr;
                                }

                                }


                                break;
                        }
                        case GAME_STATE: {
                                printf("server GAME_STATE packet\n");

                                break;
                        }
                        case MOVE_COMMAND: {
                                printf("server MOVE_COMMAND packet\n");
                        break;
                        }
                        case IMPULSE_COMMAND: {
                                printf("server IMPULSE_COMMAND packet\n");
                        break;
                        }

                        case BUID_COMMAND: {

                                if (header.size < 101)
                                {
                                //      char data[100];
                                        char *dataBuildCommand = NULL;


                                // Deserialize data payload
                                if (dataBuildCommand) delete[] dataBuildCommand;
                                if (header.size > 0) {
                                        dataBuildCommand = new char[header.size];
                                        memcpy(dataBuildCommand, buf + sizeof(MessageHeader), header.size);

                                printf("server BUID_COMMAND packet\n");

                        //      char client_ip[INET_ADDRSTRLEN];
                        //      inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
                                int client_port = ntohs(client_address.sin_port);
                                //std::string client_key = std::string(client_ip) + ":" + std::to_string(client_port);

                        //      std::string clientkeyIP = server_info->connected_clients[client_key];
                                int owner_id =  0; // FIX ME
                                for(int i=0;i <  server_info->clientinfos.size(); i++)
                                {
                                        if(server_info->clientinfos[i].get()->client_address.sin_addr.s_addr == client_address.sin_addr.s_addr && server_info->clientinfos[i].get()->client_address.sin_port == client_address.sin_port)
                                        {
                                                owner_id= server_info->clientinfos[i].get()->iPlayerID;
                                        }

                                }
                        //      dataBuildCommand
                                        BuildCommand cmdGotBuild;
                                        memcpy((void*)&cmdGotBuild, dataBuildCommand, header.size);
                                        printf("cmdBack:\n");
                                        printf("cmdBack.object_id:%d\n", cmdGotBuild.object_id);
                                        printf("cmdBack.sequence_number:%d\n", cmdGotBuild.sequence_number);
                                        printf("cmdBack.position:%f %f %f\n", cmdGotBuild.position.x, cmdGotBuild.position.y , cmdGotBuild.position.z);


                                AddCube2(cmdGotBuild.position.x, cmdGotBuild.position.y , cmdGotBuild.position.z, cmdGotBuild.object_id,  owner_id);

                                }
                                else {
                                        dataBuildCommand = nullptr;
                                }

                                }

                        break;
                        }

                        case ERROR_MESSAGE: {
                                printf("server ERROR_MESSAGE packet\n");
                        break;
                        }

                //    char szBufSendBack[101];


                        //now reply the client with the same data
        //              if (sendto(server_fd, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        //              {
        //                      printf("sendto()");
        //              }


                        }

                        memset(&client_address, 0, sizeof(client_address));
                        push_packets_to_clients(server_info);

                        std::this_thread::sleep_for(std::chrono::milliseconds((long int)server_info->tickRate));
                }

                return nullptr;
 }

// In a worker thread, when you need to send a message back to the client
// You already have 'client_info->client_address' from the incoming packet
// ...
//std::vector<char> packet_to_send; // Fill with your message data
//enqueue_packet(packet_to_send, client_info->client_address);


void *udp_server_sendto_particular_client(void* arg)
{
        // 1. Cast the void* argument back to our struct type.
                ClientInfo* client_info = static_cast<ClientInfo*>(arg);

                // 2. IMPORTANT: Copy the data to the thread's own stack and free the heap memory.
                // This prevents memory leaks and ensures the main thread doesn't have to worry
                // about the lifetime of the pointer it passed.
                int server_socket_fd = client_info->server_socket_fd;
                struct sockaddr_in client_addr = client_info->client_address;
                socklen_t slen = sizeof(client_addr);
           // delete client_info; // Free the allocated memory

                // Get client IP and port for logging
                char client_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
                int client_port = ntohs(client_addr.sin_port);

                std::cout << "[Thread " << pthread_self() << "] Handling client " << client_ip << ":" << client_port << std::endl;

                bool isClientLoopRunning = true;


        while(isClientLoopRunning)
        {
                                #define MAX_UDP_PACKET_SIZE2 101
                                char buf[MAX_UDP_PACKET_SIZE2];

                        //if(clientinfo->iNumAuthGot > 0)
                                if(client_info->iNumAuthGot > 0)
                        {
                                        #define MAX_UDP_PACKET_SIZE2 101

                                                char sz_packet_buffer[MAX_UDP_PACKET_SIZE2];

                                                MessageHeader header;


                                                printf("Sending Packet: to next_player_id:%d \n", next_player_id);

                                header.type = JOIN_REQUEST;
                                header.size = sizeof(JoinRequestCommand);

                                                printf("header.type: %d\n",header.type);
                                                printf("header.size: %d\n", header.size);

                                                //memcpy(&header, buf, sizeof(MessageHeader));

                                                memcpy(sz_packet_buffer, &header , sizeof(MessageHeader));

                                                JoinRequestCommand cmdSend;
                                                 cmdSend.uiRequestID = next_player_id;
                                                 cmdSend.uiThreadLoopNum = 1; //uiThreadLoopNum;
                                                 cmdSend.uiConnected = 1 ;//uiConnected;
                                        // sprintf(cmd.szCRC64Code, "%s", "FEWOkf233F#@OKF#@OKf#FO#@kfk3okfl;k3f32wjf32kjf32k3j2foi3fo3jf3f");// our temp password
                                                 sprintf(cmdSend.szCRC64Code, "%s", "Welcome to Alliance & Allegence");// our temp password
                                                 memcpy(sz_packet_buffer+sizeof(MessageHeader ) , &cmdSend , sizeof(JoinRequestCommand));
                                                   // inextplayerid
                                                        // "Welcome to Alliance & Allegence"
                                                        int send_len= 0;
                                                        send_len = sizeof(MessageHeader );

                                                        send_len = send_len + sizeof(JoinRequestCommand);


                                                                //now reply the client with the same data
                                                                        if (sendto(server_socket_fd, sz_packet_buffer, send_len, 0, (struct sockaddr*) &client_addr, slen) == -1)
                                                                        {
                                                                               printf("sendto()");
                                                                        }
                                                client_info->iNumAuthGot--;

                                if(client_info->iNumAuthGot < 0)
                                {
                                client_info->iNumAuthGot=0;

                                }
                                continue;

                        }
                        else
                        {

                        std::unique_lock<std::mutex> lock(client_info->outgoing_mutex);
      //  outgoing_cv.wait(lock, [] { return !clientinfo->outgoing_queue.empty(); });

          client_info->outgoing_cv.wait(lock, [client_info] { return !client_info->outgoing_queue.empty(); });
// https://www.mathworks.com/help/bugfinder/ref/multiplethreadswaitingonsameconditionvariable.html
// A std::condition_variable is a synchronization primitive in C++ that allows threads to wait until a specific condition becomes true. It works in conjunction with a std::mutex to protect shared data.
// Imagine you have a producer thread that adds items to a queue and a consumer thread that removes them. The consumer needs to wait if the queue is empty.
//Instead of constantly checking the queue in a loop (a process known as busy-waiting), the consumer thread can block using a std::condition_variable and wait to be notified by the producer when a new item is available.

//Here's how the general workflow operates:
//A waiting thread (the consumer in our example) locks a std::mutex.
//It then checks if the condition is met (is the queue not empty?).
//If the condition is false, it calls the wait() method on the std::condition_variable. This call automatically atomically releases the mutex and puts the thread into a waiting state.
//A notifying thread (the producer) adds a new item to the queue.
//It then locks the same mutex, modifies the shared data, and then calls notify_one() or notify_all() on the std::condition_variable.
//The notify_one() call wakes up one of the waiting threads. notify_all() wakes up all of them.
//The awakened waiting thread automatically re-acquires the mutex and resumes execution.
//It then re-checks the condition. This is important because of a phenomenon called spurious wakeups, where a thread can wake up without a notification.
//In essence, std::condition_variable provides an efficient way for threads to communicate and manage shared resources, avoiding the performance overhead of busy-waiting.

// https://www.mathworks.com/help/bugfinder/ref/multiplethreadswaitingonsameconditionvariable.html

        OutgoingPacket packet = client_info->outgoing_queue.front();
        client_info->outgoing_queue.pop();
        lock.unlock();

        // Send the packet
       // sendto(server_socket_fd,
       //        packet.data_buffer.data(),
       //        packet.data_buffer.size(),
       //        0,
       //        (struct sockaddr*)&packet.client_address,
       //        sizeof(packet.client_address));
                        // {

                                //if (sendto(server_socket_fd, packet_buffer.data(), packet_buffer.size(), 0, (sockaddr*)&client_addr, slen) == -1) {
                                        if (sendto(server_socket_fd, packet.data_buffer.data(), packet.data_buffer.size(), 0, (sockaddr*)&client_addr, slen) == -1) {
                                                std::cout << "sendto failed: " <<
                                                  // WSAGetLastError()
                                                                #if defined(_WIN32)
                                                                //#define GETSOCKETERRNO() (WSAGetLastError())
                                                                WSAGetLastError()
                                                                #else
                                                                errno
                                                        //      #define GETSOCKETERRNO() (errno)
                                                                #endif
                                                                        << std::endl;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds((long int)client_info->tickRate)); // get rid of this ssoon
                                // }
                        }
        }
        return nullptr;
}

void enqueue_packet(const std::vector<char>& data,ClientInfo& clientinfo )//const sockaddr_in& client_addr)
{
    OutgoingPacket packet;
    packet.data_buffer = data;
 //   packet.client_address = client_addr;

    std::lock_guard<std::mutex> lock(clientinfo.outgoing_mutex);
    clientinfo.outgoing_queue.push(packet);
    clientinfo.outgoing_cv.notify_one();
}

// Update the function signature

// the function to make packet go to all clients
void broadcast_packet(ServerInfo* server_info, const std::vector<char>& data_to_broadcast)
{
   // std::vector<sockaddr_in> clients_to_send_to;
   std::lock_guard<std::mutex> lock(server_info->clientinfo_mutex);
        for(size_t  i =0 ; i <server_info->clientinfos.size(); i++)
    {


     //   for (const auto& pair : connected_clients)
        //      {
            // Retrieve client address from your map's value or another structure
            // Note: The provided code stores a thread ID, not the address.
            // You would need to store the address in the map as well.
            // For example: map<string, ClientInfo*> or a custom struct.
            // Let's assume you have a way to get the address.
            // clients_to_send_to.push_back(pair.second->client_address);

                        // enqueue_packet(data_to_broadcast, clientinfo);

                          enqueue_packet(data_to_broadcast,  *(server_info->clientinfos[i]) );
      //  }
    } // Lock is released here

   // for (const auto& addr : clients_to_send_to) {
   //     enqueue_packet(data_to_broadcast, addr);
   // }
}
void push_packets_to_clients(ServerInfo* server_info) // (void* arg), this function would be pushed/refacted into running on its own thread like PhysicsThread.
{
        printf("push_packets_to_clients() cubes.size(): %d\n", cubes.size());

        for(size_t i =0; i < cubes.size(); i++)
        {
                MessageHeader header;
                                        header.type = GAME_STATE;

                                        header.size = sizeof(Cube);

                                        //send_message_udp2(header, (const char*)&cmd);
                                        //bool send_message_udp2(const MessageHeader & header, const char* data) {
                                        // Send header and data in a single packet to minimize overhead
                                        std::vector<char> packet_buffer(sizeof(MessageHeader) + header.size);
                                        memcpy(packet_buffer.data(), &header, sizeof(MessageHeader));
                                        if (header.size > 0) {


                                                Cube cmd;
                                                cmd.position.x =        cubes[i].position.x;
                                                cmd.position.y =        cubes[i].position.y;
                                                cmd.position.z =        cubes[i].position.z;

                                                cmd.velocity.x =        cubes[i].velocity.x;
                                                cmd.velocity.y =        cubes[i].velocity.y;
                                                cmd.velocity.z =        cubes[i].velocity.z;

                                                cmd.halfSize =  cubes[i].halfSize;
                                                cmd.iRenderType =       cubes[i].iRenderType;
                                                cmd.iHighLight[0] =     cubes[i].iHighLight[0];
                                                cmd.iHighLight[1] =     cubes[i].iHighLight[1];
                                                cmd.iHighLight[2] =     cubes[i].iHighLight[2];
                                                cmd.iHighLight[3] =     cubes[i].iHighLight[3];

                                                cmd.owner_id =  cubes[i].owner_id;
                                                cmd.id =        cubes[i].id;
                                                /*
                                                 NetworkVector3 velocity;
                float halfSize;

                uint32_t iRenderType;
                // The following vectors cannot be sent directly and must be serialized
                // separately into a buffer. I've commented them out for clarity.
                // std::vector<float> uvCoordinatesPerTriangleArray;
                // std::vector<float> vvtype;

                uint32_t iHighLight[4];

                uint32_t owner_id;
                uint32_t id;*/

                                                memcpy(packet_buffer.data() + sizeof(MessageHeader), (const void*)&cmd, header.size);
                                                broadcast_packet(server_info,packet_buffer);

                                        }

        }
}

//      sendto

//udp_server_sendto_all_clients
 //   sendto prioritypackets            // new actions from players, physics collided objects
//      sendto somestate                  // around player and random packets



        //void disconnectClient(std::string client_key, ClientInfo* client_info)
        void disconnectClient(std::string client_key, ServerInfo* server_info)
        {
                  // Optional: Remove client from map upon exit
          ///  std::string client_key = std::string(client_ip) + ":" + std::to_string(client_port);
          //  {
                        std::lock_guard<std::mutex> lock(server_info->clients_mutex);
                        server_info->connected_clients.erase(client_key);
           // }
          //int iCloseOK =close( client_info.server_socket_fd);


                // close connection
        }


        void AddCube(float x, float y, float z, int id, int owner_id)
        {
                   Cube newCube;

           newCube.halfSize = 0.5f;
           newCube.position.x = x;
           newCube.position.y = y;
           newCube.position.z = z;

           newCube.velocity.x = 0.0f;
           newCube.velocity.y = 0.0f;
           newCube.velocity.z = 0.0f;
           newCube.iRenderType = 1;

           // The vector is automatically constructed here
         //  newCube.vvtype.push_back(33.0f);
           newCube.iHighLight[0] = 33;
           newCube.iHighLight[1] = 34;
           newCube.iHighLight[2] = 35;
           newCube.iHighLight[3] = 36;

                newCube.id = id;
                newCube.owner_id = owner_id;

           // Push a copy of the temporary object into the vector
           cubes.push_back(newCube);
        }
void AddCube2(float x, float y, float z, int id, int owner_id)
        {
                   Cube newCube;

           newCube.halfSize = 0.5f;
           newCube.position.x = x;
           newCube.position.y = y;
           newCube.position.z = z;

           newCube.velocity.x = 0.0f;
           newCube.velocity.y = 0.0f;
           newCube.velocity.z = 0.0f;
           newCube.iRenderType = 1;

           // The vector is automatically constructed here
         //  newCube.vvtype.push_back(33.0f);
           newCube.iHighLight[0] = 33;
           newCube.iHighLight[1] = 34;
           newCube.iHighLight[2] = 35;
           newCube.iHighLight[3] = 36;

                newCube.id = cubes.size();

        //      newCube.object_id = id;
                newCube.owner_id = owner_id;

           // Push a copy of the temporary object into the vector
           cubes.push_back(newCube);
        }
        void initCubes()
        {

        //      cubes.push_back

         int random_number = 10 + rand() % (25 - 10 + 1);


         AddCube(
                 (float)rand() * static_cast<float>(random_number) / (float)RAND_MAX,
                 (float)rand() * static_cast<float>(random_number) / (float)RAND_MAX,
                 (float)rand() * static_cast<float>(random_number) / (float)RAND_MAX
         ,1, 0);

         AddCube(
                 1.0f,
                1.0f,
                 1.0f
         ,2, 0);

         AddCube(
                 2.0f,
                 2.0f,
                 2.0f
        ,3, 0 );

         }

