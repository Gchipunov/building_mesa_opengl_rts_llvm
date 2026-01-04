
#ifndef CREATE_SPAWN_PACKET_SENDER
#define CREATE_SPAWN_PACKET_SENDER

#if defined(_WIN32) || defined(_WIN64)_

#pragma once
#endif

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "BuildStructure_Cube.h"
#include "common_multiplayer5.h"
#include "UDP_Client_Class.h"

class CreateSpawnPacketSender
{
public:
	CreateSpawnPacketSender();
	~CreateSpawnPacketSender();

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	void  SendNewBox(float x, float y, float z);


};

extern CreateSpawnPacketSender* p_gCreateSpawnPacketSender;


#endif