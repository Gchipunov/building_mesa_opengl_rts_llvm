#include "Blender-Camera-Class.h"

// https://www.youtube.com/watch?v=QaYOQB2e36g Good Camera for RTS - How To Make an RTS Camera In Unity 6 w/ Input System and Cinemachine 3


// Constants for camera behavior
const float PAN_SPEED = 0.01f;
const float ORBIT_SENSITIVITY = 0.1f;
const float ZOOM_SPEED = 0.5f;

// Private members to handle camera state
// These are not in the provided header but are necessary for the logic.
// They would typically be declared in a private section of the header.
//float m_screen_width;
//float m_screen_height;
//float m_distance;
//float m_yaw;
//float m_pitch;

// Constructor: Initializes the camera with default values for a Blender-style
// Z-up orbiting camera.
BlenderCameraClass::BlenderCameraClass(int screen_width, int screen_height)
	: BaseCameraClass(screen_width, screen_height)
{
	m_screen_width = static_cast<float>(screen_width);
	m_screen_height = static_cast<float>(screen_height);

	// Set initial Blender-style Z-up camera parameters
	cameraPos = glm::vec3(5.0f, -5.0f, 3.0f); // A good starting position
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Calculate initial distance
	m_distance = glm::distance(cameraPos, cameraTarget);

	// Calculate initial yaw and pitch from the starting position
	// This ensures consistency. The math for a Z-up system is slightly different.
	glm::vec3 direction = glm::normalize(cameraTarget - cameraPos);
	m_yaw = glm::degrees(atan2(direction.y, direction.x));
	m_pitch = glm::degrees(asin(direction.z));

	// Initial calculation of the view and projection matrices
	viewMatrix = GetViewMatrix();
	projectionMatrix = GetProjectionMatrix();

	// Initialize the base class members for consistency
	camera_position = cameraPos;
	camera_front = glm::normalize(cameraTarget - cameraPos);
	camera_up = upDirection;
	camera_right = glm::normalize(glm::cross(camera_front, camera_up));
}

// Destructor
BlenderCameraClass::~BlenderCameraClass()
{
	// No dynamic memory to free
}

// Returns the calculated view matrix. This is the core of the camera class.
// It uses glm::lookAt to create a view matrix that looks from `cameraPos`
// to `cameraTarget` with the correct `upDirection`.
glm::mat4 BlenderCameraClass::GetViewMatrix() const
{
	// https://archive.org/embed/GDC2015Fiedler/GDC2015-Fiedler.mp4
	return glm::lookAt(cameraPos, cameraTarget, upDirection);
	printf("Blender camera.x: %f,camera.y: %f,camera.z: %f,cameraTarget.x: %f,cameraTarget.y: %f,cameraTarget.z: %f\n ",
		cameraTarget.x, cameraTarget.y, cameraTarget.z, cameraTarget.x, cameraTarget.y, cameraTarget.z
	);

}

// Returns the calculated projection matrix. This is independent of the
// camera's orientation or position, only depending on FOV and aspect ratio.
glm::mat4 BlenderCameraClass::GetProjectionMatrix()
{
	// camera_projection = glm::perspective(glm::radians(camera_fov), (float)screen_width / (float)screen_height, 0.1f, 100.0f);
	//return glm::perspective(glm::radians(45.0f), m_screen_width / m_screen_height, 0.1f, 100.0f);

	return glm::perspective(glm::radians(45.0f), (float)m_screen_width / (float)m_screen_height, 0.1f, 100.0f);
}

// Handles keyboard input. In Blender, keyboard input is not the primary
// way to control the camera's position, but this can be used for panning.
void BlenderCameraClass::ProcessKeyboard(camera_movement_t direction, float delta_time)
{
	// Calculate the local right and forward vectors in the Z-up plane
	glm::vec3 right = glm::normalize(glm::cross(camera_front, upDirection));
	glm::vec3 forward_planar = glm::normalize(glm::cross(upDirection, right));

	switch (direction)
	{
	case FORWARD:
		cameraTarget += forward_planar * PAN_SPEED;
		break;
	case BACKWARD:
		cameraTarget -= forward_planar * PAN_SPEED;
		break;
	case LEFT:
		cameraTarget -= right * PAN_SPEED;
		break;
	case RIGHT:
		cameraTarget += right * PAN_SPEED;
		break;
	default:
		break;
	}

	// Recalculate camera position after panning the target
	cameraPos = cameraTarget - camera_front * m_distance;
}

// Handles mouse movement for orbiting. This is the main method for
// manipulating a Blender-style camera.
void BlenderCameraClass::ProcessMouseMovement(float xpos, float ypos, float clamp_pitch)
{

	// We need to keep track of the last mouse position to calculate the delta
	static float lastX = xpos;
	static float lastY = ypos;
	static bool firstMouse = true;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Reversed Y-axis for intuitive rotation
	lastX = xpos;
	lastY = ypos;

	xoffset *= ORBIT_SENSITIVITY;
	yoffset *= ORBIT_SENSITIVITY;

	// Update yaw and pitch
//	m_yaw += xoffset;
	m_yaw -= xoffset;
	m_pitch += yoffset;

	// Clamp the pitch to prevent camera flipping over
	if (clamp_pitch)
	{
		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;
	}

	// Recalculate the camera's front vector based on updated yaw and pitch
	// Note: The rotation order is important for a Z-up system.
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_pitch));
	camera_front = glm::normalize(front);

	// Recalculate camera position
	cameraPos = cameraTarget - camera_front * m_distance;

	// Update base class members
	camera_position = cameraPos;
	camera_up = upDirection;
	camera_right = glm::normalize(glm::cross(camera_front, camera_up));
}

// Handles mouse scrolling for dolly zooming.
void BlenderCameraClass::ProcessMouseScroll(float yscroll)
{
	m_distance -= yscroll * ZOOM_SPEED;

	// Clamp the distance to prevent the camera from going through the target
	if (m_distance < 0.1f)
	{
		m_distance = 0.1f;
	}

	// Recalculate the camera position based on the new distance
	cameraPos = cameraTarget - camera_front * m_distance;
}





/*
#include "BlenderCameraClass.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

// Constants for camera behavior
const float PAN_SPEED = 0.01f;
const float ORBIT_SENSITIVITY = 0.1f;
const float ZOOM_SPEED = 0.5f;
*/
// Constructor: Initializes the camera with default values.
BlenderCameraClass2::BlenderCameraClass2(int screen_width, int screen_height)
	: BaseCameraClass(screen_width, screen_height)

	//: m_screen_width(static_cast<float>(screen_width)),
//	m_screen_height(static_cast<float>(screen_height)),
	//: 


{

	m_screen_width = ((screen_width));
	m_screen_height = ((screen_height));

	m_distance = (5.0f);
	Mouse_lastX = (0.0f);
	Mouse_lastY = (0.0f);
	Mouse_first_frame = (true);

	// Set initial Blender-style Z-up camera parameters
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Initial camera position relative to target
	camera_position = glm::vec3(0.0f, -m_distance, 0.0f);

	// Initial orientation: looking down the positive Y-axis from behind
	orientation = glm::quat(glm::vec3(glm::radians(-45.0f), 0.0f, 0.0f));
	// static_cast<float>
	Update(); // Call update to set initial vectors and matrices
}

// Destructor
BlenderCameraClass2::~BlenderCameraClass2()
{
	// No dynamic memory to free
}

// Updates the camera's front, right, and up vectors based on the current quaternion orientation.
// This is the core of the quaternion-based camera.
void BlenderCameraClass2::Update()
{
	// Recalculate camera vectors from the quaternion
	glm::mat4 rotation_matrix = glm::toMat4(orientation);
	camera_front = glm::normalize(glm::vec3(rotation_matrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f))); // Assumes default is +Y forward
	camera_right = glm::normalize(glm::cross(camera_front, upDirection));
	camera_up = glm::normalize(glm::cross(camera_right, camera_front));

	// Recalculate camera position for orbiting
	camera_position = cameraTarget - camera_front * m_distance;

	// Recalculate the view matrix
	camera_view = glm::lookAt(camera_position, cameraTarget, camera_up);
}

// Returns the calculated view matrix.
glm::mat4 BlenderCameraClass2::GetViewMatrix() const
{
	return camera_view;
}

// Returns the calculated projection matrix.
glm::mat4 BlenderCameraClass2::GetProjectionMatrix()
{
	camera_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_screen_width) / static_cast<float>(m_screen_height), 0.1f, 100.0f);
	return camera_projection;
}

// Handles keyboard input for panning the camera target.
void BlenderCameraClass2::ProcessKeyboard(camera_movement_t direction, float delta_time)
{
	glm::vec3 right = glm::normalize(glm::cross(camera_front, upDirection));
	glm::vec3 forward_planar = glm::normalize(glm::cross(upDirection, right));

	switch (direction)
	{
	case FORWARD:
		cameraTarget += forward_planar * PAN_SPEED;
		break;
	case BACKWARD:
		cameraTarget -= forward_planar * PAN_SPEED;
		break;
	case LEFT:
		cameraTarget -= right * PAN_SPEED;
		break;
	case RIGHT:
		cameraTarget += right * PAN_SPEED;
		break;
	}
	Update();
}

// Handles mouse movement for orbiting the camera.
void BlenderCameraClass2::ProcessMouseMovement(float xpos, float ypos,
	//	mouse_button_t button_t,
	float clamp_pitch)
{
	//if (button_t == LEFT_BUTTON) // Only orbit on left-mouse drag
	{
		if (Mouse_first_frame)
		{
			Mouse_lastX = xpos;
			Mouse_lastY = ypos;
			Mouse_first_frame = false;
		}

		float xoffset = (xpos - Mouse_lastX) * ORBIT_SENSITIVITY;
		float yoffset = (Mouse_lastY - ypos) * ORBIT_SENSITIVITY;
		Mouse_lastX = xpos;
		Mouse_lastY = ypos;

		// Create rotation quaternions
		glm::quat yaw_rotation = glm::angleAxis(glm::radians(xoffset), upDirection);
		glm::quat pitch_rotation = glm::angleAxis(glm::radians(yoffset), camera_right);

		// Apply rotations to the orientation quaternion
		orientation = pitch_rotation * orientation; // Order is important!
		orientation = yaw_rotation * orientation;
		orientation = glm::normalize(orientation);

		Update();
	}
}

// Handles mouse scrolling for dolly zooming.
void BlenderCameraClass2::ProcessMouseScroll(float yscroll)
{
	m_distance -= yscroll * ZOOM_SPEED;

	// Clamp the distance to prevent the camera from going through the target
	if (m_distance < 0.1f)
	{
		m_distance = 0.1f;
	}

	Update();
}


/*

#include "BlenderCameraClass3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

// Constants for camera behavior
const float PAN_SPEED = 0.01f;
const float ORBIT_SENSITIVITY = 0.1f;
const float ZOOM_SPEED = 0.5f;
*/

// Constructor: Initializes the camera with default values.



BlenderCameraClass3::BlenderCameraClass3(int screen_width, int screen_height)
	: BaseCameraClass(screen_width, screen_height)
{
	// Set initial Blender-style Z-up camera parameters
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Initialize the camera's internal state
	m_screen_width = static_cast<float>(screen_width);
	m_screen_height = static_cast<float>(screen_height);
	m_distance = 5.0f; // Initial distance from target
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	Mouse_lastX = m_screen_width / 2.0f;
	Mouse_lastY = m_screen_height / 2.0f;
	Mouse_first_frame = true;

	// Initial calculation of the camera's front vector
	UpdateCameraVectors();

	// Initial calculation of camera position and matrices
	UpdateMatrices();
}

// Destructor
BlenderCameraClass3::~BlenderCameraClass3()
{
	// No dynamic memory to free
}

// Recalculates the camera's position, front, right, and up vectors
// based on the current yaw, pitch, and distance.
void BlenderCameraClass3::UpdateCameraVectors()
{
	// The core logic from your BaseCameraClass for updating vectors from yaw/pitch.
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	camera_front = glm::normalize(front);

	// Recalculate camera position for orbiting
	camera_position = cameraTarget - camera_front * m_distance;

	// Calculate the other vectors based on the new front vector and the fixed up direction.
	camera_right = glm::normalize(glm::cross(camera_front, upDirection));
	camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}

// Recalculates the view and projection matrices.
void BlenderCameraClass3::UpdateMatrices()
{
	camera_view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
	//	camera_projection = glm::perspective(glm::radians(45.0f), m_screen_width / m_screen_height, 0.1f, 100.0f);
	camera_projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_screen_width) / static_cast<float>(m_screen_height), 0.1f, 100.0f);

}

// Returns the calculated view matrix.
glm::mat4 BlenderCameraClass3::GetViewMatrix() const
{
	return camera_view;
}

// Returns the calculated projection matrix.
glm::mat4 BlenderCameraClass3::GetProjectionMatrix()
{
	return camera_projection;
}

// Handles keyboard input for panning the camera target.
void BlenderCameraClass3::ProcessKeyboard(camera_movement_t direction, float delta_time)
{
	// Calculate the local right and forward vectors in the Z-up plane
	glm::vec3 right = glm::normalize(glm::cross(camera_front, upDirection));
	glm::vec3 forward_planar = glm::normalize(glm::cross(upDirection, right));

	switch (direction)
	{
	case FORWARD:
		cameraTarget += forward_planar * PAN_SPEED;
		break;
	case BACKWARD:
		cameraTarget -= forward_planar * PAN_SPEED;
		break;
	case LEFT:
		cameraTarget -= right * PAN_SPEED;
		break;
	case RIGHT:
		cameraTarget += right * PAN_SPEED;
		break;
	default:
		break;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}

// Handles mouse movement for orbiting, using the logic from BaseCameraClass.
void BlenderCameraClass3::ProcessMouseMovement(float xpos, float ypos, float clamp_pitch)
{
	if (Mouse_first_frame)
	{
		Mouse_lastX = xpos;
		Mouse_lastY = ypos;
		Mouse_first_frame = false;
	}

	float xoffset = xpos - Mouse_lastX;
	float yoffset = Mouse_lastY - ypos; // reversed since y-coordinates go from bottom to top
	Mouse_lastX = xpos;
	Mouse_lastY = ypos;

	// The sensitivity from your code
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// Update yaw and pitch
	m_yaw += xoffset;
	m_pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (clamp_pitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}

// Handles mouse scrolling for dolly zooming.
void BlenderCameraClass3::ProcessMouseScroll(float yscroll)
{
	m_distance -= yscroll * ZOOM_SPEED;

	// Clamp the distance
	if (m_distance < 0.1f)
	{
		m_distance = 0.1f;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}




// Constructor: Initializes the camera with default values.
BlenderCameraClass4::BlenderCameraClass4(int screen_width, int screen_height)
	: BaseCameraClass(screen_width, screen_height)

{
	// Set initial Blender-style Z-up camera parameters
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Initialize the camera's internal state
	m_screen_width = (screen_width);
	m_screen_height = (screen_height);
	m_distance = 5.0f; // Initial distance from target
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	Mouse_lastX = m_screen_width / 2.0f;
	Mouse_lastY = m_screen_height / 2.0f;
	Mouse_first_frame = true;

	// Initial calculation of the camera's front vector
	UpdateCameraVectors();

	// Initial calculation of camera position and matrices
	UpdateMatrices();
}

// Destructor
BlenderCameraClass4::~BlenderCameraClass4()
{
	// No dynamic memory to free
}

// Recalculates the camera's position, front, right, and up vectors
// based on the current yaw, pitch, and distance.
void BlenderCameraClass4::UpdateCameraVectors()
{
	// The core logic for updating vectors from yaw/pitch.
	// This will calculate the direction vector from the new yaw and pitch.
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	camera_front = glm::normalize(front);

	// Recalculate camera position for orbiting
	// The camera position is always 'distance' away from the target,
	// along the camera_front vector.
	camera_position = cameraTarget - camera_front * m_distance;

	// Calculate the other vectors based on the new front vector and the fixed up direction.
	camera_right = glm::normalize(glm::cross(camera_front, upDirection));
	camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}

// Recalculates the view and projection matrices.
void BlenderCameraClass4::UpdateMatrices()
{
	camera_view = glm::lookAt(camera_position, cameraTarget, camera_up);
	camera_projection = glm::perspective(glm::radians(45.0f), (float)m_screen_width / (float)m_screen_height, 0.1f, 100.0f);
}

// Returns the calculated view matrix.
glm::mat4 BlenderCameraClass4::GetViewMatrix() const
{
	return camera_view;
}

// Returns the calculated projection matrix.
glm::mat4 BlenderCameraClass4::GetProjectionMatrix()
{
	return camera_projection;
}

// Handles keyboard input for panning the camera target.
void BlenderCameraClass4::ProcessKeyboard(camera_movement_t direction, float delta_time)
{
	// Calculate the local right and forward vectors in the Z-up plane
	glm::vec3 right = glm::normalize(glm::cross(camera_front, upDirection));
	glm::vec3 forward_planar = glm::normalize(glm::cross(upDirection, right));

	switch (direction)
	{
	case FORWARD:
		cameraTarget += forward_planar * PAN_SPEED;
		break;
	case BACKWARD:
		cameraTarget -= forward_planar * PAN_SPEED;
		break;
	case LEFT:
		cameraTarget -= right * PAN_SPEED;
		break;
	case RIGHT:
		cameraTarget += right * PAN_SPEED;
		break;
	default:
		break;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}

// Handles mouse movement for orbiting, using the logic from your BaseCameraClass.
void BlenderCameraClass4::ProcessMouseMovement(float xpos, float ypos, float clamp_pitch)
{
	if (Mouse_first_frame)
	{
		Mouse_lastX = xpos;
		Mouse_lastY = ypos;
		Mouse_first_frame = false;
	}

	float xoffset = (xpos - Mouse_lastX) * ORBIT_SENSITIVITY;
	float yoffset = (Mouse_lastY - ypos) * ORBIT_SENSITIVITY;
	Mouse_lastX = xpos;
	Mouse_lastY = ypos;

	/*
	if (m_first_mouse)
	{
		m_last_x = xpos;
		m_last_y = ypos;
		m_first_mouse = false;
	}

	float xoffset = xpos - m_last_x;
	float yoffset = m_last_y - ypos; // reversed since y-coordinates go from bottom to top
	m_last_x = xpos;
	m_last_y = ypos;
	*/
	// Use the sensitivity from your BaseCameraClass
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// Update yaw and pitch
	m_yaw += xoffset;
	m_pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (clamp_pitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}

// Handles mouse scrolling for dolly zooming.
void BlenderCameraClass4::ProcessMouseScroll(float yscroll)
{
	m_distance -= yscroll * ZOOM_SPEED;

	// Clamp the distance
	if (m_distance < 0.1f)
	{
		m_distance = 0.1f;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}



// Constructor: Initializes the camera with default values for a Blender-style
// Z-up orbiting camera.
BlenderCameraClass5::BlenderCameraClass5(int screen_width, int screen_height)  //  :
//	: m_screen_width(static_cast<float>(screen_width)),
//	m_screen_height(static_cast<float>(screen_height)),
	//	m_distance(5.0f),
	//	m_last_x(0.0f),
	//	m_last_y(0.0f),
	//	m_first_mouse(true)

	: BaseCameraClass(screen_width, screen_height)
{

	m_screen_width = ((screen_width));
	m_screen_height = (screen_height);

	m_distance = (5.0f);
	// Set initial Blender-style Z-up camera parameters
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Initial camera orientation and position.
	// We'll use a quaternion to represent this.
	// Initial orientation: looking down the positive Y-axis from behind
	m_orientation = glm::quat(glm::vec3(glm::radians(-45.0f), 0.0f, 0.0f));

	// Initial calculation of the view and projection matrices
	UpdateCameraVectors();
	UpdateMatrices();

	// Initialize the base class members for consistency
	camera_position = cameraPos;
	camera_front = glm::normalize(cameraTarget - cameraPos);
	camera_up = upDirection;
	camera_right = glm::normalize(glm::cross(camera_front, camera_up));
}

// Destructor
BlenderCameraClass5::~BlenderCameraClass5()
{
	// No dynamic memory to free
}

// Recalculates the camera's position and vectors based on the quaternion orientation.
void BlenderCameraClass5::UpdateCameraVectors()
{
	// Calculate the camera's front, right, and up vectors from the quaternion orientation
	glm::mat4 rotation_matrix = glm::toMat4(m_orientation);

	// The camera looks along the Y-axis in its local space, so we transform that vector
	glm::vec3 local_front = glm::vec3(0.0f, 1.0f, 0.0f);
	camera_front = glm::normalize(glm::vec3(rotation_matrix * glm::vec4(local_front, 0.0f)));

	// Calculate the other vectors based on the new front vector and the fixed up direction.
	camera_right = glm::normalize(glm::cross(camera_front, upDirection));
	camera_up = glm::normalize(glm::cross(camera_right, camera_front));

	// Recalculate camera position for orbiting
	cameraPos = cameraTarget - camera_front * m_distance;
}

// Recalculates the view and projection matrices.
void BlenderCameraClass5::UpdateMatrices()
{
	viewMatrix = glm::lookAt(cameraPos, cameraTarget, camera_up);
	projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(m_screen_width) / static_cast<float>(m_screen_height), 0.1f, 100.0f);
}

// Returns the calculated view matrix.
glm::mat4 BlenderCameraClass5::GetViewMatrix() const
{
	return viewMatrix;
}

// Returns the calculated projection matrix.
glm::mat4 BlenderCameraClass5::GetProjectionMatrix()
{
	return projectionMatrix;
}

// Handles keyboard input.
void BlenderCameraClass5::ProcessKeyboard(camera_movement_t direction, float delta_time)
{
	// This function can be used for panning in Blender, which is what we'll do here.
	// It's a bit of a hybrid, but good for learning.
	glm::vec3 right = glm::normalize(glm::cross(camera_front, upDirection));
	glm::vec3 forward_planar = glm::normalize(glm::cross(upDirection, right));

	switch (direction)
	{
	case FORWARD:
		cameraTarget += forward_planar * PAN_SPEED;
		break;
	case BACKWARD:
		cameraTarget -= forward_planar * PAN_SPEED;
		break;
	case LEFT:
		cameraTarget -= right * PAN_SPEED;
		break;
	case RIGHT:
		cameraTarget += right * PAN_SPEED;
		break;
	default:
		break;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}

// Handles mouse movement for orbiting, panning, or zooming based on button state.
void BlenderCameraClass5::ProcessMouseMovement(float xpos, float ypos

	, float clamppitch

	//, mouse_button_t button_t
	//, int mouse_button
)
{

	//	int mouse_button
		/*
		// Initialize mouse state on the first frame
		if (Mouse_first_frame)
		{
			Mouse_lastX = xpos;
			Mouse_lastY = ypos;
			m_first_mouse = false;
		}

		float xoffset = (xpos - m_last_x);
		float yoffset = (m_last_y - ypos); // reversed Y-axis for intuitive rotation
		m_last_x = xpos;
		m_last_y = ypos;

	//	if (button_t == MIDDLE_BUTTON)
		if (mouse_button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			// Orbit: Rotate the camera around the target point
			xoffset *= ORBIT_SENSITIVITY;
			yoffset *= ORBIT_SENSITIVITY;

			glm::quat pitch_rotation = glm::angleAxis(glm::radians(yoffset), camera_right);
			glm::quat yaw_rotation = glm::angleAxis(glm::radians(xoffset), upDirection);

			// Order is important: apply yaw, then pitch
			m_orientation = pitch_rotation * m_orientation * yaw_rotation;
			m_orientation = glm::normalize(m_orientation);
		}
	//	else if (button_t == MIDDLE_BUTTON_SHIFT)
		else if (button_t == GLFW_MOD_SHIFT)
		{
			// Pan: Move the camera target
			xoffset *= PAN_SPEED;
			yoffset *= PAN_SPEED;

			glm::vec3 right = glm::normalize(glm::cross(camera_front, upDirection));
			glm::vec3 up = upDirection;

			cameraTarget -= right * xoffset;
			cameraTarget += up * yoffset;
		}

		UpdateCameraVectors();
		UpdateMatrices();
		*/


		// Initialize mouse state on the first frame
		// Initialize mouse state on the first frame
	if (Mouse_first_frame)
	{
		Mouse_lastX = xpos;
		Mouse_lastY = ypos;
		Mouse_first_frame = false;
	}

	float xoffset = (xpos - Mouse_lastX);
	float yoffset = (Mouse_lastY - ypos); // reversed Y-axis for intuitive rotation
	Mouse_lastX = xpos;
	Mouse_lastY = ypos;

	// Check the state variables to determine the action
	if (is_middle_button_pressed) {
		if (is_shift_pressed) {
			// Pan: Move the camera target
			xoffset *= PAN_SPEED;
			yoffset *= PAN_SPEED;

			glm::vec3 right = glm::normalize(glm::cross(camera_front, upDirection));
			glm::vec3 up = upDirection;

			cameraTarget -= right * xoffset;
			cameraTarget += up * yoffset;
		}
		else {
			// Orbit: Rotate the camera around the target point
			xoffset *= ORBIT_SENSITIVITY;
			yoffset *= ORBIT_SENSITIVITY;

			// ... (rest of the orbit code is correct)
			glm::quat pitch_rotation = glm::angleAxis(glm::radians(yoffset), camera_right);
			glm::quat yaw_rotation = glm::angleAxis(glm::radians(xoffset), upDirection);

			// Order is important: apply yaw, then pitch
			m_orientation = pitch_rotation * m_orientation * yaw_rotation;
			m_orientation = glm::normalize(m_orientation);
		}
	}

	UpdateCameraVectors();
	UpdateMatrices();

}

// Handles mouse scrolling for dolly zooming.
void BlenderCameraClass5::ProcessMouseScroll(float yscroll)
{
	m_distance -= yscroll * ZOOM_SPEED;

	// Clamp the distance
	if (m_distance < 0.1f)
	{
		m_distance = 0.1f;
	}

	UpdateCameraVectors();
	UpdateMatrices();
}


//------------------------------------------------------
//-----------------------------------------------------------------------
//---------------------------------------------------------

BlenderCameraClass6::BlenderCameraClass6(int screen_width, int screen_height)
	: BaseCameraClass(screen_width, screen_height)
{



	m_screen_width = (screen_width);
	m_screen_height = (screen_height);

	// Set initial Blender-style Z-up camera parameters
	glm::vec3	cameraPos = glm::vec3(5.0f, -5.0f, 3.0f); // A good starting position
	glm::vec3	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3	upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Calculate initial distance
//	m_distance = glm::distance(cameraPos, cameraTarget);

	// Calculate initial yaw and pitch from the starting position
	// This ensures consistency. The math for a Z-up system is slightly different.
//	glm::vec3 direction = glm::normalize(cameraTarget - cameraPos);
//float	m_yaw = glm::degrees(atan2(direction.y, direction.x));
//float	m_pitch = glm::degrees(asin(direction.z));
//	m_distance = glm::distance(cameraPos, cameraTarget);

	// Calculate the initial camera direction vector
	glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPos);

	// The `quatLookAt` function constructs a quaternion that orients a camera
	// to "look" in a specified direction with a given up vector.
	// Since OpenGL/GLM cameras typically look down the negative Z-axis,
	// we use that as the default forward vector for the `quatLookAt` calculation.
	// This is often `glm::vec3(0.0f, 0.0f, -1.0f)`.
	// However, for a Blender-style camera, the convention can be different.
	// We'll create the quaternion directly from the initial orientation vectors.

	// A simpler and more robust way to create the initial quaternion is to use
	// the `quatLookAt` function. It takes the camera's direction and up vector.
	// Note: GLM's `quatLookAt` builds a rotation that maps `(0,0,-1)` (default camera front)
	// to `cameraDirection` while maintaining `upDirection`.

	// Since we are using a custom `GetViewMatrix` that takes position and orientation,
	// the quaternion needs to be the camera's world orientation.
	// We can get this by constructing a lookAt matrix and then converting it to a quaternion.
	glm::mat4 view_matrix = glm::lookAt(cameraPos, cameraTarget, upDirection);
	orientation = glm::quat_cast(glm::inverse(view_matrix));

	/*
	// Initialize the base class members
	camera_position = cameraPos;
	camera_front = glm::normalize(cameraTarget - cameraPos);
	camera_up = upDirection;

	// The camera_right vector is derived from the orientation quaternion.
	// You can calculate it like this:
	glm::vec3 default_right_vector = glm::vec3(1.0f, 0.0f, 0.0f);
	camera_right = orientation * default_right_vector;

	// Remove the m_yaw and m_pitch as they are no longer needed
	// with a quaternion-based camera.

	// Initial calculation of the view and projection matrices
	// We pass the new quaternion and position to the GetViewMatrix function.
	camera_view = GetViewMatrix(orientation, camera_position);
	camera_projection = GetProjectionMatrix();
	*/


	// Initialize the base class members for consistency
	camera_position = cameraPos;
	camera_front = glm::normalize(cameraTarget - cameraPos);
	camera_up = upDirection;
	camera_right = glm::normalize(glm::cross(camera_front, camera_up));

	//	glm::vec3 camera_position;
	// glm::vec3 camera_front;
	//	glm::vec3 camera_up;
	//	glm::vec3 camera_right; // unknown if have to support for base working vec3(-1.0, 0.0, 0.0) my guess the blender default 

		// Initial calculation of the view and projection matrices
	camera_view = GetViewMatrix();
	camera_projection = GetProjectionMatrix();

}
BlenderCameraClass6::~BlenderCameraClass6()
{

}
void BlenderCameraClass6::ProcessKeyboard(camera_movement_t direction, float delta_time) {
	float velocity = movement_speed * delta_time;
	if (direction == FORWARD) {
		//   position = heim_vec3f_add(position,
		//       heim_vec3f_mul(heim_vec3f_normalize(front), velocity));
		camera_position = camera_position + (glm::normalize(camera_front) * velocity);
	}
	if (direction == BACKWARD) {
		//     position = heim_vec3f_sub(position,
		 //        heim_vec3f_mul(heim_vec3f_normalize(front), velocity));
		camera_position = camera_position - (glm::normalize(camera_front) * velocity);
	}
	if (direction == LEFT) {
		// position = heim_vec3f_sub(position,
		//     heim_vec3f_mul(
		 //        heim_vec3f_normalize(heim_vec3f_cross(front, up)), velocity));

		 //   position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
		camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * velocity;

	}
	if (direction == RIGHT) {
		//    position = heim_vec3f_add(camera->position,
		//        heim_vec3f_mul(
		//            heim_vec3f_normalize(heim_vec3f_cross(front, up)), velocity));

		camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * velocity;
	}
	if (direction == UP) {
		//     position = heim_vec3f_add(camera->position,
		  //       heim_vec3f_mul(heim_vec3f_normalize(up), velocity));
		camera_position += camera_position + (glm::normalize(camera_up) * velocity);

	}
	if (direction == DOWN) {
		// position = heim_vec3f_sub(position,
		//     heim_vec3f_mul(heim_vec3f_normalize(up), velocity));
		camera_position -= camera_position + (glm::normalize(camera_up) * velocity);

	}

	camera_projection = glm::perspective(glm::radians(camera_fov), (float)m_screen_width / (float)m_screen_height, 0.1f, 100.0f);
	camera_view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
} //: A virtual function for handling keyboard input.

void BlenderCameraClass6::ProcessMouseMovement(float xpos, float ypos, float clamppitch) {
	// float xpos = static_cast<float>(xposIn);
	// float ypos = static_cast<float>(yposIn);

	if (Mouse_first_frame)
	{
		Mouse_lastX = xpos;
		Mouse_lastY = ypos;
		Mouse_first_frame = false;
	}

	float xoffset = xpos - Mouse_lastX;
	float yoffset = Mouse_lastY - ypos; // reversed since y-coordinates go from bottom to top
	Mouse_lastX = xpos;
	Mouse_lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera_yaw += xoffset;
	camera_pitch += yoffset;

	glm::quat rot = glm::angleAxis(camera_yaw, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::angleAxis(camera_pitch, glm::vec3(1.0f, 0.0f, 0.0f));

	//camera.orientation = camera.orientation 

	orientation = orientation * rot;
	/*
		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (camera_pitch > 89.0f)
			camera_pitch = 89.0f;
		if (camera_pitch < -89.0f)
			camera_pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
		front.y = sin(glm::radians(camera_pitch));
		front.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
		camera_front = glm::normalize(front);

		camera_projection = glm::perspective(glm::radians(camera_fov), (float)m_screen_width / (float)m_screen_height, 0.1f, 100.0f);
		camera_view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);


		*/
}// : A virtual function for handling mouse movement.

glm::mat4 BlenderCameraClass6::GetViewMatrix(
	//const glm::quat& orientation, const glm::vec3& position
) const {
	const glm::vec3& position = camera_position;
	// 1. Convert the quaternion rotation to a 4x4 rotation matrix.
	// This is the inverse rotation because the view matrix needs to rotate the world
	// in the opposite direction of the camera's rotation.
	glm::mat4 rotation_matrix = glm::toMat4(glm::inverse(orientation));

	// 2. Create a translation matrix to move the world by the camera's negative position.
	// This is also the inverse translation.
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), -position);

	// 3. Combine the rotation and translation.
	// The order of multiplication is crucial. You want to first translate the world
	// and then rotate it. So, the translation matrix goes on the right.
	return rotation_matrix * translation_matrix;
}
glm::mat4  BlenderCameraClass6::GetProjectionMatrix() //: Returns the glm::mat4 projection matrix.
{

	return camera_projection;

}
void BlenderCameraClass6::ProcessMouseScroll(float yscroll) {

	//    fov -= (float)yscroll;
	camera_fov -= yscroll;
	if (camera_fov < 1.0f)
		camera_fov = 1.0f;
	// if (fov > 45.0f)
   //      fov = 45.0f;
   //      if (fov > 450.0f)
   //      fov = 450.0f;
	if (camera_fov > 100.0f)
		camera_fov = 100.0f;
}//: A virtual function for handling mouse scrolling.


/*

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Assume this is your class header with the new member
// glm::quat orientation;

BlenderCameraClass6::BlenderCameraClass6(int screen_width, int screen_height)
	: BaseCameraClass(screen_width, screen_height)
{
	m_screen_width = (screen_width);
	m_screen_height = (screen_height);

	// Set initial Blender-style Z-up camera parameters
	glm::vec3 cameraPos = glm::vec3(5.0f, -5.0f, 3.0f); // A good starting position
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Calculate initial distance
	m_distance = glm::distance(cameraPos, cameraTarget);

	// Calculate the initial camera direction vector
	glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPos);

	// The `quatLookAt` function constructs a quaternion that orients a camera
	// to "look" in a specified direction with a given up vector.
	// Since OpenGL/GLM cameras typically look down the negative Z-axis,
	// we use that as the default forward vector for the `quatLookAt` calculation.
	// This is often `glm::vec3(0.0f, 0.0f, -1.0f)`.
	// However, for a Blender-style camera, the convention can be different.
	// We'll create the quaternion directly from the initial orientation vectors.

	// A simpler and more robust way to create the initial quaternion is to use
	// the `quatLookAt` function. It takes the camera's direction and up vector.
	// Note: GLM's `quatLookAt` builds a rotation that maps `(0,0,-1)` (default camera front)
	// to `cameraDirection` while maintaining `upDirection`.

	// Since we are using a custom `GetViewMatrix` that takes position and orientation,
	// the quaternion needs to be the camera's world orientation.
	// We can get this by constructing a lookAt matrix and then converting it to a quaternion.
	glm::mat4 view_matrix = glm::lookAt(cameraPos, cameraTarget, upDirection);
	orientation = glm::quat_cast(glm::inverse(view_matrix));

	// Initialize the base class members
	camera_position = cameraPos;
	camera_front = glm::normalize(cameraTarget - cameraPos);
	camera_up = upDirection;

	// The camera_right vector is derived from the orientation quaternion.
	// You can calculate it like this:
	glm::vec3 default_right_vector = glm::vec3(1.0f, 0.0f, 0.0f);
	camera_right = orientation * default_right_vector;

	// Remove the m_yaw and m_pitch as they are no longer needed
	// with a quaternion-based camera.

	// Initial calculation of the view and projection matrices
	// We pass the new quaternion and position to the GetViewMatrix function.
	camera_view = GetViewMatrix(orientation, camera_position);
	camera_projection = GetProjectionMatrix();
}

BlenderCameraClass6::~BlenderCameraClass6()
{
}

void BlenderCameraClass6::ProcessKeyboard(camera_movement_t direction, float delta_time) {
	// ... (no changes needed here as it uses camera_front, camera_up, camera_position)
	float velocity = movement_speed * delta_time;
	if (direction == FORWARD) {
		camera_position += camera_front * velocity;
	}
	if (direction == BACKWARD) {
		camera_position -= camera_front * velocity;
	}
	if (direction == LEFT) {
		camera_position -= camera_right * velocity;
	}
	if (direction == RIGHT) {
		camera_position += camera_right * velocity;
	}
	if (direction == UP) {
		camera_position += camera_up * velocity;
	}
	if (direction == DOWN) {
		camera_position -= camera_up * velocity;
	}

	camera_projection = glm::perspective(glm::radians(camera_fov), (float)m_screen_width / (float)m_screen_height, 0.1f, 100.0f);
	camera_view = GetViewMatrix(orientation, camera_position);
}

void BlenderCameraClass6::ProcessMouseMovement(float xpos, float ypos, float clamppitch) {
	if (Mouse_first_frame)
	{
		Mouse_lastX = xpos;
		Mouse_lastY = ypos;
		Mouse_first_frame = false;
	}

	float xoffset = xpos - Mouse_lastX;
	float yoffset = Mouse_lastY - ypos; // reversed since y-coordinates go from bottom to top
	Mouse_lastX = xpos;
	Mouse_lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// Use quaternions to incrementally rotate the camera.
	// We rotate around the world's Z-axis for yaw, and the camera's local right axis for pitch.
	// Get the camera's local right vector from its current orientation.
	glm::vec3 camera_right = orientation * glm::vec3(1.0f, 0.0f, 0.0f); // Assuming local right is (1,0,0)

	// Create rotation quaternions for pitch and yaw.
	glm::quat pitch_rotation = glm::angleAxis(glm::radians(yoffset), camera_right);
	glm::quat yaw_rotation = glm::angleAxis(glm::radians(xoffset), glm::vec3(0.0f, 0.0f, 1.0f));

	// Combine the rotations and apply to the camera's orientation.
	// The order is important: yaw around world Z, then pitch around local right.
	orientation = yaw_rotation * pitch_rotation * orientation;

	// Update the camera's front and up vectors based on the new orientation
	// Assuming the camera's local front is (0, -1, 0) and up is (0, 0, 1)
	camera_front = orientation * glm::vec3(0.0f, -1.0f, 0.0f);
	camera_up = orientation * glm::vec3(0.0f, 0.0f, 1.0f);

	// Normalize vectors to prevent floating-point errors from accumulating
	camera_front = glm::normalize(camera_front);
	camera_up = glm::normalize(camera_up);

	// Recalculate camera_right from the new front and up vectors
	camera_right = glm::normalize(glm::cross(camera_front, camera_up));

	// Now update the view matrix using the new orientation
	camera_view = GetViewMatrix(orientation, camera_position);
}

// (The rest of the code remains the same)
// glm::mat4 BlenderCameraClass6::GetViewMatrix(const glm::quat& orientation, const glm::vec3& position)
// void BlenderCameraClass6::ProcessMouseScroll(float yscroll)
*/

//#include <glm/glm.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>

// Assume this is your class header with the new member
// glm::quat orientation;

BlenderCameraClass7::BlenderCameraClass7(int screen_width, int screen_height)
	: BaseCameraClass(screen_width, screen_height)
{
	m_screen_width = (screen_width);
	m_screen_height = (screen_height);

	// Set initial Blender-style Z-up camera parameters
	glm::vec3 cameraPos = glm::vec3(5.0f, -5.0f, 3.0f); // A good starting position
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 upDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Z is UP!

	// Calculate initial distance
	float	m_distance = glm::distance(cameraPos, cameraTarget);

	// Calculate the initial camera direction vector
	glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPos);

	// The `quatLookAt` function constructs a quaternion that orients a camera
	// to "look" in a specified direction with a given up vector.
	// Since OpenGL/GLM cameras typically look down the negative Z-axis,
	// we use that as the default forward vector for the `quatLookAt` calculation.
	// This is often `glm::vec3(0.0f, 0.0f, -1.0f)`.
	// However, for a Blender-style camera, the convention can be different.
	// We'll create the quaternion directly from the initial orientation vectors.

	// A simpler and more robust way to create the initial quaternion is to use
	// the `quatLookAt` function. It takes the camera's direction and up vector.
	// Note: GLM's `quatLookAt` builds a rotation that maps `(0,0,-1)` (default camera front)
	// to `cameraDirection` while maintaining `upDirection`.

	// Since we are using a custom `GetViewMatrix` that takes position and orientation,
	// the quaternion needs to be the camera's world orientation.
	// We can get this by constructing a lookAt matrix and then converting it to a quaternion.
	glm::mat4 view_matrix = glm::lookAt(cameraPos, cameraTarget, upDirection);
	orientation = glm::quat_cast(glm::inverse(view_matrix));

	// Initialize the base class members
	camera_position = cameraPos;
	camera_front = glm::normalize(cameraTarget - cameraPos);
	camera_up = upDirection;

	// The camera_right vector is derived from the orientation quaternion.
	// You can calculate it like this:
	glm::vec3 default_right_vector = glm::vec3(1.0f, 0.0f, 0.0f);
	camera_right = orientation * default_right_vector;

	// Remove the m_yaw and m_pitch as they are no longer needed
	// with a quaternion-based camera.

	// Initial calculation of the view and projection matrices
	// We pass the new quaternion and position to the GetViewMatrix function.
	camera_view = GetViewMatrix(orientation, camera_position);
	camera_projection = GetProjectionMatrix();
}

BlenderCameraClass7::~BlenderCameraClass7()
{
}

void BlenderCameraClass7::ProcessKeyboard(camera_movement_t direction, float delta_time) {
	// ... (no changes needed here as it uses camera_front, camera_up, camera_position)
	float velocity = movement_speed * delta_time;
	/*
	if (direction == FORWARD) {
		camera_position += camera_front * velocity;
	}
	if (direction == BACKWARD) {
		camera_position -= camera_front * velocity;
	}
	if (direction == LEFT) {
		camera_position -= camera_right * velocity;
	}
	if (direction == RIGHT) {
		camera_position += camera_right * velocity;
	}
	if (direction == UP) {
		camera_position += camera_up * velocity;
	}
	if (direction == DOWN) {
		camera_position -= camera_up * velocity;
	}
	*/

	if (direction == FORWARD) {

		camera_position -= camera_up * velocity;
	}
	if (direction == BACKWARD) {
		camera_position += camera_up * velocity;
	}
	if (direction == LEFT) {
		camera_position -= camera_right * velocity;
	}
	if (direction == RIGHT) {
		camera_position += camera_right * velocity;
	}
	if (direction == UP) {
		camera_position -= camera_front * velocity;
	}
	if (direction == DOWN) {
		camera_position += camera_front * velocity;
	}

	camera_projection = glm::perspective(glm::radians(camera_fov), (float)m_screen_width / (float)m_screen_height, 0.1f, 100.0f);
	camera_view = GetViewMatrix(orientation, camera_position);
}

void BlenderCameraClass7::ProcessMouseMovement(float xpos, float ypos, float clamppitch) {
	if (Mouse_first_frame)
	{
		Mouse_lastX = xpos;
		Mouse_lastY = ypos;
		Mouse_first_frame = false;
	}

	//	float xoffset = xpos - Mouse_lastX;
	float xoffset = Mouse_lastX - xpos; //reversed for right left correct default fps feeling
	float yoffset = Mouse_lastY - ypos; // reversed since y-coordinates go from bottom to top
	Mouse_lastX = xpos;
	Mouse_lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// Use quaternions to incrementally rotate the camera.
	// We rotate around the world's Z-axis for yaw, and the camera's local right axis for pitch.
	// Get the camera's local right vector from its current orientation.
	glm::vec3 camera_right2 = orientation * glm::vec3(1.0f, 0.0f, 0.0f); // Assuming local right is (1,0,0)

	// Create rotation quaternions for pitch and yaw.
	glm::quat pitch_rotation = glm::angleAxis(glm::radians(yoffset), camera_right2);
	glm::quat yaw_rotation = glm::angleAxis(glm::radians(xoffset), glm::vec3(0.0f, 0.0f, 1.0f));

	// Combine the rotations and apply to the camera's orientation.
	// The order is important: yaw around world Z, then pitch around local right.
	orientation = yaw_rotation * pitch_rotation * orientation;

	// Update the camera's front and up vectors based on the new orientation
	// Assuming the camera's local front is (0, -1, 0) and up is (0, 0, 1)
	camera_front = orientation * glm::vec3(0.0f, -1.0f, 0.0f);
	camera_up = orientation * glm::vec3(0.0f, 0.0f, 1.0f);

	// Normalize vectors to prevent floating-point errors from accumulating
	camera_front = glm::normalize(camera_front);
	camera_up = glm::normalize(camera_up);

	// Recalculate camera_right from the new front and up vectors
//	camera_right = glm::normalize(glm::cross(camera_front, camera_up));

	camera_right = orientation * glm::vec3(1.0f, 0.0f, 0.0f);;
	camera_right = glm::normalize(camera_right);

	// Now update the view matrix using the new orientation
	camera_view = GetViewMatrix(orientation, camera_position);
}

// (The rest of the code remains the same)
// glm::mat4 BlenderCameraClass7::GetViewMatrix(const glm::quat& orientation, const glm::vec3& position)
void BlenderCameraClass7::ProcessMouseScroll(float yscroll) {

	//    fov -= (float)yscroll;
	camera_fov -= yscroll;
	if (camera_fov < 1.0f)
		camera_fov = 1.0f;
	// if (fov > 45.0f)
   //      fov = 45.0f;
   //      if (fov > 450.0f)
   //      fov = 450.0f;
	if (camera_fov > 100.0f)
		camera_fov = 100.0f;
}//: A virtual function for handling mouse scrolling.

glm::mat4 BlenderCameraClass7::GetViewMatrix(const glm::quat& orientation, const glm::vec3& position) const {

	// 1. Convert the quaternion rotation to a 4x4 rotation matrix.

	// This is the inverse rotation because the view matrix needs to rotate the world

	// in the opposite direction of the camera's rotation.

	glm::mat4 rotation_matrix = glm::toMat4(glm::inverse(orientation));



	// 2. Create a translation matrix to move the world by the camera's negative position.

	// This is also the inverse translation.

	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), -position);



	// 3. Combine the rotation and translation.

	// The order of multiplication is crucial. You want to first translate the world

	// and then rotate it. So, the translation matrix goes on the right.

	return rotation_matrix * translation_matrix;

}

glm::mat4 BlenderCameraClass7::GetViewMatrix() const
{

	// camera_view = GetViewMatrix(orientation, camera_position);

	// return camera_view;

	return GetViewMatrix(orientation, camera_position);
}

glm::mat4  BlenderCameraClass7::GetProjectionMatrix() //: Returns the glm::mat4 projection matrix.
{

	return camera_projection;

}

// WebGL Quat-Camera-Example:

// https://gchipunov.github.io/QuatCamera/Mod5.html