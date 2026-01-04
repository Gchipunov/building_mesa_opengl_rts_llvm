#ifndef BUILDSTRUCTURE_CUBE_CAST_H
#define BUILDSTRUCTURE_CUBE_CAST_H


#ifdef WIN32
#pragma once
#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "common_multiplayer5.h"

#include "Base-Camera-Class.h"
#include "Blender-Camera-Class.h"

#include "Ray_cast_glm_mouse.h"
#include "Terrian_GridPlane.h"

#include "QuatCamera.h"
#include "Cursor_UI_Draw.h"

#include "DrawLine_as_Cube.h"

#include "Create-Spawn_Packet-Sender.h"

class CreateSpawnPacketSender;

// prototyping casting a building , placement
class BuildStructure_Cube
{

public:
	BuildStructure_Cube();
	~BuildStructure_Cube();

	int AddCubeBuild(float x, float y, float z, float width);

	void UpdateCastLocationCube(float x, float y, float z, float width);

	void UpdateCastLocationCube2(float x, float y, float z, float width, float vvtype);

	void UpdateCastLocationCube3(float x, float y, float z, float width, float vvtype, int textureID);

	int CastCubeIndex;


	NetworkVector3 placement_position;
	int iRenderState;


	int NumberOfVertsInObject;


	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_callback(GLFWwindow* window, float xposIn, float yposIn);


	CreateSpawnPacketSender* m_CreateSpawnPacketSender;
};// g_pBuildStructure_Cube

extern BuildStructure_Cube* g_pBuildStructure_Cube;


#endif
