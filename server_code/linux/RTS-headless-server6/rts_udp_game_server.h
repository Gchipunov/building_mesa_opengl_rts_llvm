#ifndef UDP_SERVER_CLASS_H
#define UDP_SERVER_CLASS_H


        #include <iostream>
        #include <vector>
        #include <map>
        #include <thread>
        #include <mutex>
        #include <chrono>
        #include <unistd.h>
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <cstring>
        #include <cmath>

        #include <stdio.h>
        #include <stdlib.h>
        //#include <unistd.h>
        //#include <errno.h>

        #if defined(_WIN32)
        #include <winsock2.h>
        //#define GETSOCKETERRNO() (WSAGetLastError())
        #else
        #include <errno.h>
        //#define GETSOCKETERRNO() (errno)
        #endif


        #include <string.h>
        #include <sys/types.h>
        //#include <sys/socket.h>
        #include <netinet/in.h>
        //#include <arpa/inet.h>
        #include <netdb.h>

        #include <pthread.h>    // threading includes
#include <queue>      //
#include <condition_variable>




// A structure to hold the data and destination for a single outgoing packet
struct OutgoingPacket {
    std::vector<char> data_buffer;

   // sockaddr_in client_address;
};


        struct ClientInfo {
                int server_socket_fd;
                struct sockaddr_in client_address;
                int iPlayerID;
                long long LastTimeGotPacket;       // for timeout disconnect;//
                float tickRate;                   // custom rate for rate client get sent things
                int iNumAuthGot ;//= 0;  // so that don't have to sendto in recvfrom only loop, need this variable to authenticate, then reauthenticate players


                // Thread-safe queue for outgoing packets
                std::queue<OutgoingPacket> outgoing_queue;
                std::mutex outgoing_mutex;
                std::condition_variable outgoing_cv;

                 // Constructor to properly initialize members
    ClientInfo() :
        server_socket_fd(0),
        iPlayerID(0),
        LastTimeGotPacket(0),
        tickRate(0.0f),
        iNumAuthGot(0)
    {
        // For default-constructed members like std::queue, mutex, and condition_variable,
        // no explicit initialization is required in the initializer list.
        // Their default constructors are automatically called.
    }
        };


struct ServerInfo {
        int server_socket_fd;
        struct sockaddr_in server_address;
        int iServerID;

                long long LastTimeGotPacket;       // for timeout disconnect;//
                float tickRate;                   // custom rate for rate client get sent things

                char szServerIP[64];
                // ----------------------------

                        std::map<std::string, pthread_t> connected_clients;
                        std::mutex clients_mutex; // Mutex to protect access to the map
                //      std::vector <ClientInfo> clientinfos;
                // Corrected declaration inside a struct/class
                std::vector<std::unique_ptr<ClientInfo>> clientinfos;

                        std::mutex clientinfo_mutex; // Mutex to protect access to the map

};


        // A map to keep track of connected clients to avoid creating multiple threads for the same client.
        // Key: "ip:port", Value: pthread_t (the thread ID)
        // moved to server object to gain thread pointer access
//      std::map<std::string, pthread_t> connected_clients;
//      std::mutex clients_mutex; // Mutex to protect access to the map
//      std::vector <ClientInfo> clientinfos;
//      std::mutex clientinfo_mutex; // Mutex to protect access to the map

// need to refactor ClientInfo struct into rts_udp_game_server.h
        //void disconnectClient(std::string client_key, ClientInfo* client_info); // re need to revamp the need and log player disconnecting for game logic
        void disconnectClient(std::string client_key, ServerInfo* server_info);
// make server side ai take over for temp actions, or allow teammates to control players



        bool socket_linux_connect_clients();


void *get_in_addr(struct sockaddr *sa);
bool socket_linux_init();


void initGameTCPCentralServerChatInfoGame();


void UpdatePhysics(); // the Cubes physics;
void UpdateGameLogic(); // the Cubes physics;



void * udp_server_receive_only_thread (void* arg);
void *udp_server_sendto_particular_client(void* arg);





void AddCube(float x, float y, float z, int id, int owner_id);
void initCubes();

void enqueue_packet(const std::vector<char>& data, ClientInfo& clientinfo);
void broadcast_packet(ServerInfo* server_info, const std::vector<char>& data_to_broadcast);
void push_packets_to_clients(ServerInfo* server_info);


#define MAXBUFLEN 100

#endif
