#ifndef COMMON_MULTIPLAYER_H
#define COMMON_MULTIPLAYER_H

#pragma once

#include <cstdint> // Use fixed-size integer types for portability
//#include "glm/glm.hpp"

// Use this pragma to ensure structs are packed tightly in memory,
// removing any padding the compiler might add for alignment.
// This is CRITICAL for network communication.
#pragma pack(push, 1)

// Enumeration for different message types
enum MessageType : uint32_t { // Explicitly define as a 32-bit unsigned int
    JOIN_REQUEST,
    GAME_STATE,
    MOVE_COMMAND,
    IMPULSE_COMMAND,
    ERROR_MESSAGE
};

// A simple header for all messages using fixed-size types
struct MessageHeader {
    uint32_t type;
    uint32_t size;
};

// Represents a 3D vector using fixed-size floats
struct NetworkVector3 {
    float x, y, z;
};

// Represents a physics object (a cube) in the game world
struct Cube {
    NetworkVector3 position;
    NetworkVector3 velocity;
    float halfSize;

    uint32_t iRenderType;
    // The following vectors cannot be sent directly and must be serialized
    // separately into a buffer. I've commented them out for clarity.
    // std::vector<float> uvCoordinatesPerTriangleArray;
    // std::vector<float> vvtype;

    uint32_t iHighLight[4];

    uint32_t owner_id;
    uint32_t id;
};

// Represents the full game state at a given tick
struct WorldState {
    uint64_t tick; // Use 64-bit for tick to prevent overflow
    // The cubes vector must be serialized into a buffer manually.
    // std::vector<Cube> cubes;
};

// A command sent from a client to the server to move an object
struct MoveCommand {
    uint32_t player_id;
    uint32_t object_id;
    NetworkVector3 destination;
};

struct JoinRequestCommand {
    uint32_t uiRequestID;
    uint32_t uiThreadLoopNum;
    uint32_t uiConnected;
    char szCRC64Code[65];
};

// New: A command to apply an impulse to a physics object
struct ImpulseCommand {
    uint32_t player_id;
    uint32_t object_id;
    NetworkVector3 direction;
    float strength;
};

// Re-enable padding after the structs are defined
#pragma pack(pop)


// https://huggingface.co/spaces/MeYourHint/MoMask

#endif // COMMON_H
