#ifndef COMMON_MULTIPLAYER_H
#define COMMON_MULTIPLAYER_H

#pragma once

#include <cstdint> // Use fixed-size integer types for portability
 // #include "glm/glm.hpp"



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
        BUID_COMMAND,
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

struct BuildCommand {
        // uint32_t player_id; // use ip map key to get player_id so don't have to send throuh wire
        uint32_t object_id; // type of structure/ template object
        // uint32_t objectnumber_id;    // upgrade level
        uint32_t sequence_number;                               // sequence number
        //uint32_t shared_type;
        // uint32_t build_speed; // how fast should pop upgrade
        // uint32_t faction_id;
        // uint32_t other_var;
        NetworkVector3 position;
};

// Re-enable padding after the structs are defined
#pragma pack(pop)


#endif // COMMON_H
