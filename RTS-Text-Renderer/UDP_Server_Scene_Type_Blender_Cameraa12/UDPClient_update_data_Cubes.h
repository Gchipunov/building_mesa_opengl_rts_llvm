
#ifndef UDPCCLIENT_CUBES_DATA_UPDATE_H
#define UDPCCLIENT_CUBES_DATA_UPDATE_H

#include "UDPClient_update-AABB-Cubes.h"


#ifdef WIN32
#pragma once

#endif


struct CubeGraphicsData
{
	uint32_t mainVerticesIndex;


};

void UpdateDataCubes(std::vector<Cube>& cubes, std::vector<CubeGraphicsData>& cubeGraphicsData); //, float deltaTime);


extern std::vector <CubeGraphicsData> cubeGraphicsData;

extern int g_syncCubes;
#endif