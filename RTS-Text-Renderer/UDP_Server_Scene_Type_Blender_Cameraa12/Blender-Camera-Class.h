#ifndef BLENDER_CAMERA_CLASS_H
#define BLENDER_CAMERA_CLASS_H


#ifdef WIN32
#pragma once
#endif




//#include <iostream>
#include <vector>
#include "Base-Camera-Class.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

class BlenderCameraClass : public BaseCameraClass
{
public:
	BlenderCameraClass(int screen_width, int screen_height);
	~BlenderCameraClass();

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

	// 1. Define camera position and target in a Z-up world
	glm::vec3 cameraPos;// = glm::vec3(0.0f, -5.0f, 2.0f); // 5 units back, 2 units up
	glm::vec3 cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);  // Looking at the world origin

	// 2. Define the world's "up" direction as the positive Z-axis
	glm::vec3 upDirection;// = glm::vec3(0.0f, 0.0f, 1.0f);

	// 3. Create the view matrix using glm::lookAt
	glm::mat4 viewMatrix;// = glm::lookAt(cameraPos, cameraTarget, upDirection);

	// The projection matrix doesn't need to change.
	// It's independent of the world's "up" direction.
	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	glm::quat orientation;


	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	//BaseCameraClass(int screen_width, int screen_height);
	//~BaseCameraClass();

	virtual glm::mat4  GetViewMatrix() const; //: Returns the glm::mat4 view matrix.

	virtual glm::mat4 GetProjectionMatrix();//: Returns the glm::mat4 projection matrix.

	virtual void ProcessKeyboard(camera_movement_t direction, float delta_time); //: A virtual function for handling keyboard input.

	virtual void ProcessMouseMovement(float xpos, float ypos, float clamppitch);// : A virtual function for handling mouse movement.

	virtual void ProcessMouseScroll(float yscroll); //: A virtual function for handling mouse scrolling.

	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
	glm::vec3 camera_right; // unknown if have to support for base working vec3(-1.0, 0.0, 0.0) my guess the blender default 




	glm::mat4 camera_projection;
	glm::mat4 camera_view;
	float m_distance;

	float m_yaw;
	float m_pitch;


};




class BlenderCameraClass2 : public BaseCameraClass
{
public:
	BlenderCameraClass2(int screen_width, int screen_height);
	~BlenderCameraClass2();

	//#include <glm/glm.hpp>
	//#include <glm/gtc/matrix_transform.hpp>

		// 1. Define camera position and target in a Z-up world
	glm::vec3 cameraPos;// = glm::vec3(0.0f, -5.0f, 2.0f); // 5 units back, 2 units up
	glm::vec3 cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);  // Looking at the world origin

	// 2. Define the world's "up" direction as the positive Z-axis
	glm::vec3 upDirection;// = glm::vec3(0.0f, 0.0f, 1.0f);

	// 3. Create the view matrix using glm::lookAt
	glm::mat4 viewMatrix;// = glm::lookAt(cameraPos, cameraTarget, upDirection);

	// The projection matrix doesn't need to change.
	// It's independent of the world's "up" direction.
	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	glm::quat orientation;


	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	//BaseCameraClass(int screen_width, int screen_height);
	//~BaseCameraClass();

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


	void Update();
	float m_distance;

};




class BlenderCameraClass3 : public BaseCameraClass
{
public:
	BlenderCameraClass3(int screen_width, int screen_height);
	~BlenderCameraClass3();

	//#include <glm/glm.hpp>
	//#include <glm/gtc/matrix_transform.hpp>

		// 1. Define camera position and target in a Z-up world
	glm::vec3 cameraPos;// = glm::vec3(0.0f, -5.0f, 2.0f); // 5 units back, 2 units up
	glm::vec3 cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);  // Looking at the world origin

	// 2. Define the world's "up" direction as the positive Z-axis
	glm::vec3 upDirection;// = glm::vec3(0.0f, 0.0f, 1.0f);

	// 3. Create the view matrix using glm::lookAt
	glm::mat4 viewMatrix;// = glm::lookAt(cameraPos, cameraTarget, upDirection);

	// The projection matrix doesn't need to change.
	// It's independent of the world's "up" direction.
	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	glm::quat orientation;


	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	//BaseCameraClass(int screen_width, int screen_height);
	//~BaseCameraClass();

	virtual glm::mat4  GetViewMatrix() const; //: Returns the glm::mat4 view matrix.

	virtual glm::mat4 GetProjectionMatrix(); //: Returns the glm::mat4 projection matrix.

	virtual void ProcessKeyboard(camera_movement_t direction, float delta_time); //: A virtual function for handling keyboard input.

	virtual void ProcessMouseMovement(float xpos, float ypos, float clamppitch
		//	, mouse_button_t button_t
	);// : A virtual function for handling mouse movement.

	virtual void ProcessMouseScroll(float yscroll); //: A virtual function for handling mouse scrolling.

	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
	glm::vec3 camera_right; // unknown if have to support for base working vec3(-1.0, 0.0, 0.0) my guess the blender default 




	glm::mat4 camera_projection;
	glm::mat4 camera_view;


	//void Update();
	float m_distance;
	void UpdateCameraVectors();
	void UpdateMatrices();

	float m_yaw;
	float m_pitch;

};






class BlenderCameraClass4 : public BaseCameraClass
{
public:
	BlenderCameraClass4(int screen_width, int screen_height);
	~BlenderCameraClass4();

	//#include <glm/glm.hpp>
	//#include <glm/gtc/matrix_transform.hpp>

		// 1. Define camera position and target in a Z-up world
	glm::vec3 cameraPos;// = glm::vec3(0.0f, -5.0f, 2.0f); // 5 units back, 2 units up
	glm::vec3 cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);  // Looking at the world origin

	// 2. Define the world's "up" direction as the positive Z-axis
	glm::vec3 upDirection;// = glm::vec3(0.0f, 0.0f, 1.0f);

	// 3. Create the view matrix using glm::lookAt
	glm::mat4 viewMatrix;// = glm::lookAt(cameraPos, cameraTarget, upDirection);

	// The projection matrix doesn't need to change.
	// It's independent of the world's "up" direction.
	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	glm::quat orientation;


	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	//BaseCameraClass(int screen_width, int screen_height);
	//~BaseCameraClass();

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


	//void Update();
	float m_distance;
	void UpdateCameraVectors();
	void UpdateMatrices();

	float m_yaw;
	float m_pitch;

};



class BlenderCameraClass5 : public BaseCameraClass
{
public:
	BlenderCameraClass5(int screen_width, int screen_height);
	~BlenderCameraClass5();

	//#include <glm/glm.hpp>
	//#include <glm/gtc/matrix_transform.hpp>

		// 1. Define camera position and target in a Z-up world
	glm::vec3 cameraPos;// = glm::vec3(0.0f, -5.0f, 2.0f); // 5 units back, 2 units up
	glm::vec3 cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);  // Looking at the world origin

	// 2. Define the world's "up" direction as the positive Z-axis
	glm::vec3 upDirection;// = glm::vec3(0.0f, 0.0f, 1.0f);

	// 3. Create the view matrix using glm::lookAt
	glm::mat4 viewMatrix;// = glm::lookAt(cameraPos, cameraTarget, upDirection);

	// The projection matrix doesn't need to change.
	// It's independent of the world's "up" direction.
	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	glm::quat orientation;


	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	//BaseCameraClass(int screen_width, int screen_height);
	//~BaseCameraClass();

	virtual glm::mat4  GetViewMatrix() const; //: Returns the glm::mat4 view matrix.

	virtual glm::mat4 GetProjectionMatrix(); //: Returns the glm::mat4 projection matrix.

	virtual void ProcessKeyboard(camera_movement_t direction, float delta_time); //: A virtual function for handling keyboard input.

	virtual void ProcessMouseMovement(float xpos, float ypos, float clamppitch
		//	, mouse_button_t button_t
		//	, int mouse_button
	);// : A virtual function for handling mouse movement.

	virtual void ProcessMouseScroll(float yscroll); //: A virtual function for handling mouse scrolling.

	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
	glm::vec3 camera_right; // unknown if have to support for base working vec3(-1.0, 0.0, 0.0) my guess the blender default 




	glm::mat4 camera_projection;
	glm::mat4 camera_view;


	//void Update();
	float m_distance;
	void UpdateCameraVectors();
	void UpdateMatrices();


	// State tracking for mouse buttons and modifiers
	bool is_middle_button_pressed = false;
	bool is_shift_pressed = false;
	glm::quat m_orientation;

};




class BlenderCameraClass6 : public BaseCameraClass
{
public:
	BlenderCameraClass6(int screen_width, int screen_height);
	~BlenderCameraClass6();

	//#include <glm/glm.hpp>
	//#include <glm/gtc/matrix_transform.hpp>

		// 1. Define camera position and target in a Z-up world
	glm::vec3 cameraPos;// = glm::vec3(0.0f, -5.0f, 2.0f); // 5 units back, 2 units up
	glm::vec3 cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);  // Looking at the world origin

	// 2. Define the world's "up" direction as the positive Z-axis
	glm::vec3 upDirection;// = glm::vec3(0.0f, 0.0f, 1.0f);

	// 3. Create the view matrix using glm::lookAt
//	glm::mat4 viewMatrix;// = glm::lookAt(cameraPos, cameraTarget, upDirection);

	// The projection matrix doesn't need to change.
	// It's independent of the world's "up" direction.
//	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	glm::quat orientation;


	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	//BaseCameraClass(int screen_width, int screen_height);
	//~BaseCameraClass();

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


	//void Update();
	float m_distance;
	void UpdateCameraVectors();
	void UpdateMatrices();
};




class BlenderCameraClass7 : public BaseCameraClass
{
public:
	BlenderCameraClass7(int screen_width, int screen_height);
	~BlenderCameraClass7();

	//#include <glm/glm.hpp>
	//#include <glm/gtc/matrix_transform.hpp>

		// 1. Define camera position and target in a Z-up world
	glm::vec3 cameraPos;// = glm::vec3(0.0f, -5.0f, 2.0f); // 5 units back, 2 units up
	glm::vec3 cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);  // Looking at the world origin

	// 2. Define the world's "up" direction as the positive Z-axis
	glm::vec3 upDirection;// = glm::vec3(0.0f, 0.0f, 1.0f);

	// 3. Create the view matrix using glm::lookAt
//	glm::mat4 viewMatrix;// = glm::lookAt(cameraPos, cameraTarget, upDirection);

	// The projection matrix doesn't need to change.
	// It's independent of the world's "up" direction.
//	glm::mat4 projectionMatrix;// = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

	glm::quat orientation;


	//BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window);
	//BaseCameraClass(int screen_width, int screen_height);
	//~BaseCameraClass();

	virtual glm::mat4  GetViewMatrix() const; //: Returns the glm::mat4 view matrix.

	virtual glm::mat4 GetProjectionMatrix(); //: Returns the glm::mat4 projection matrix.

	virtual void ProcessKeyboard(camera_movement_t direction, float delta_time); //: A virtual function for handling keyboard input.

	virtual void ProcessMouseMovement(float xpos, float ypos, float clamppitch);// : A virtual function for handling mouse movement.

	virtual void ProcessMouseScroll(float yscroll); //: A virtual function for handling mouse scrolling.

	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
	glm::vec3 camera_right; // unknown if have to support for base working vec3(-1.0, 0.0, 0.0) my guess the blender default 




	//	glm::mat4 camera_projection;
	//	glm::mat4 camera_view;


		//void Update();
	//	float m_distance;
	//	void UpdateCameraVectors();
	//	void UpdateMatrices();
	//	glm::quat orientation;
		// newer method to get View Matrix:
	glm::mat4	GetViewMatrix(const glm::quat& orientation, const glm::vec3& position) const;

};

#endif