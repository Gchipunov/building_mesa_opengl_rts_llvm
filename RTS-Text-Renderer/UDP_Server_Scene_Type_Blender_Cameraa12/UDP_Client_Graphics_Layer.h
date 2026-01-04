
#ifndef UDP_CLIENT_GRAPHICS_LAYER_H
#define UDP_CLIENT_GRAPHICS_LAYER_H

#include <stdint.h>
#include <vector>
#include <mutex> // will be depricateed for fast double buffer shared ptr
//#include <map>
#include <unordered_map>

#define GLEW_STATIC
#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
#include <GLFW/glfw3.h>


#define GLM_ENABLE_EXPERIMENTAL 1

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "common_multiplayer5.h"



#include "UDPClient_update_data_Cubes.h"

int AddCubeNetworked(Cube newCube);


int AddCubeNetworked2(Cube newCube);
void AddNetworkQue();
int AddCubeOrUpdate(Cube newCube);


#endif