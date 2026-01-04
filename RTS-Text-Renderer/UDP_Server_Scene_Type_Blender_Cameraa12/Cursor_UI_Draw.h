#ifndef CURSOR_UI_DRAW_H
#define CURSOR_UI_DRAW_H


#ifdef WIN32
#pragma once
#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>


#include "stb_image.h"


GLuint loadCursorTexture();
int AddCursorPlane(float x, float y, float z, float width, float height);
void UpdateMousePos(float x, float y);

class Cursor_UI_Draw
{
public:
	Cursor_UI_Draw(int screen_width, int screen_height);
	~Cursor_UI_Draw();

	//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	void mouse_callback(GLFWwindow* window, float xposIn, float yposIn);

	GLuint m_CursorTexture;
	GLuint GetCursorTextureID() { return m_CursorTexture; }

	float MouseVirtualX;
	float MouseVirtualY;

private:
	bool Mouse_first_frame; // = true;
	float Mouse_lastX; // = 800.0f / 2.0;
	float Mouse_lastY;// = 600.0 / 2.0;


	int m_screen_width;
	int m_screen_height;



};

extern Cursor_UI_Draw* g_pCursor_UI_Draw;

#endif
