
#ifndef CUBESUPDATE_H
#define CUBESUPDATE_H

#define GLM_ENABLE_EXPERIMENTAL 1

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "common_multiplayer5.h"

#ifdef WIN32
#pragma once

#endif
//  #define GLM_ENABLE_EXPERIMENTAL


extern std::vector <Cube> cubes;

bool checkAABBCollision(const Cube& a, const Cube& b);
//void resolveAABBCollision(Cube& a, Cube& b);

void resolveSphereCollision(Cube& a, Cube& b);
void updateCubes(std::vector<Cube>& cubes, float deltaTime);

// https://archive.org/embed/GDC2015Fiedler/GDC2015-Fiedler.mp4
// Hermite Interpolation
// 10 snapshots per-second:

extern int g_EnableClientSidePhysics;


struct CubeData
{
    glm::vec3 position;
    glm::quat orientation;
    bool interacting;
    glm::vec3 velocity;

};
//packing data:
// ||x,y,z,w|| = 1
// x*x + y*y + z * z + w*w = 1
// w = +-sqrt(1-x*x - y*y - z*z)
// 
// we use quaternions
// https://github.com/mas-bandwidth/cubes/blob/master/protocol.h
enum PacketType
{
    PACKET_TYPE_CONNECTION_REQUEST,
    PACKET_TYPE_CONNECTION_ACCEPTED,
    PACKET_TYPE_CONNECTION_DENIED,
    PACKET_TYPE_INPUT,
    PACKET_TYPE_SNAPSHOT,
    NUM_PACKET_TYPES
};
// https://github.com/mas-bandwidth/cubes/blob/master/game.h
struct Input
{
    int iType;
    int iFlag;



};

struct StateUpdate
{
    int iPos;
    glm::vec3 vector;
    glm::mat4 matrix;


};
// https://github.com/mas-bandwidth/cubes/blob/master/packets.h

struct SyncPacket
{
    uint16_t sequence;
    Input input;
    int num_state_updates;
    StateUpdate state_updates[64];

};


// Quantize on both sides - [THE SiZE OF THE PHYSICS BLOCKS] , can be down sized in graphics end

// Need greater accuracy than interpolation

// 4096 units per-meter for position 

// 2-15-15-15 for orientation




// softer penitraction on physics Seperating axis theorm
#endif