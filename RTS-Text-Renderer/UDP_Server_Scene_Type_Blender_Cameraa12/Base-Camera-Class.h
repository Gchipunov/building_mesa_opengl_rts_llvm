#ifndef BASE_CAMERA_CLASS_H
#define BASE_CAMERA_CLASS_H


#ifdef WIN32
#pragma once
#endif

#define GLM_ENABLE_EXPERIMENTAL 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <iostream>
#include <vector>


typedef enum camera_movement_t {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
} camera_movement_t;

class BaseCameraClass
{
public:
	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	BaseCameraClass(int screen_width, int screen_height);
	~BaseCameraClass();

	virtual glm::mat4  GetViewMatrix() const; //: Returns the glm::mat4 view matrix.

	virtual glm::mat4 GetProjectionMatrix(); //: Returns the glm::mat4 projection matrix.

	virtual void ProcessKeyboard(camera_movement_t direction, float delta_time); //: A virtual function for handling keyboard input.

	virtual void ProcessMouseMovement(float xpos, float ypos, float clamppitch);// : A virtual function for handling mouse movement.

	virtual void ProcessMouseScroll(float yscroll); //: A virtual function for handling mouse scrolling.

	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
	glm::vec3 camera_right; // unknown if have to support for base working vec3(-1.0, 0.0, 0.0) my guess the blender default 




	glm::mat4 camera_projection;
	glm::mat4 camera_view;

	float camera_fov;
	float camera_yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	//float yaw = -180.0f;
	float camera_pitch;
	float movement_speed;

	int m_screen_width;// = screen_width;
	int m_screen_height;


	GLFWwindow* main_glfw3_window;


	bool Mouse_first_frame; // = true;
	float Mouse_lastX; // = 800.0f / 2.0;
	float Mouse_lastY;// = 600.0 / 2.0;


	//bool firstMouse;

};


#endif