
#ifndef CLIENT_PACKET_TO_SEND_QUEUE
#define CLIENT_PACKET_TO_SEND_QUEUE

#if defined(_WIN32) || defined(_WIN64)_

#pragma once
#endif


#include "common_multiplayer5.h"
#include <vector>
#include <cstdint> // Use fixed-size integer types for portability
// #include "glm/glm.hpp"



// Use this pragma to ensure structs are packed tightly in memory,
// removing any padding the compiler might add for alignment.
// This is CRITICAL for network communication.
#pragma pack(push, 1)


struct PacketToSend {
	MessageHeader header;
	std::vector<char> data;




};


// Re-enable padding after the structs are defined
#pragma pack(pop)



#endif