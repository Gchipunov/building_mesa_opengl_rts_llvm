

// https://codereview.stackexchange.com/questions/286502/multi-client-socket-communication-with-thread-pool-in-c


#ifndef UDP_CLIENT_CLASS_H
#define UDP_CLIENT_CLASS_H


#define GLM_ENABLE_EXPERIMENTAL 1

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "common_multiplayer5.h"

#include <stdint.h>


#include "UDP_Client_Graphics_Layer.h"

//#include <WinSock2.h>

struct Header
{
    uint16_t sequence;
    uint16_t ack;
    uint32_t ack_bits;
};

const int BufferSize = 1024;

//uint32_t sequence_buffer[BufferSize];

extern uint32_t sequence_buffer[];;

struct PacketData
{
    bool acked;
};

//PacketData packet_data[BufferSize];

//PacketData* GetPacketData(uint16_t sequence)
//{
//    const int index = sequence % BufferSize;
//    if (sequence_buffer[index] == sequence)
//        return &packet_data[index];
//    else
//        return NULL;
//}
extern PacketData packet_data[];

extern PacketData* GetPacketData(uint16_t sequence);



extern bool winsock_init();

extern bool winsock_connect();

extern int UDP_Client_Class_Connect();




extern int  GetClientID();

extern bool send_message_udp_queue(const MessageHeader& header, const char* data);

extern int g_iMyUserIDClientID;


// New thread function for sending packets from the queue
extern void SendPacketInQue_queue(void* sock2);

extern bool send_message_udp_queue_queue(const MessageHeader& header, const char* data);

#endif
