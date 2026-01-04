#include <glm/glm.hpp>

#include "Base-Camera-Class.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.001f;
const float ZOOM = 45.0f;

//BaseCameraClass::BaseCameraClass(int screen_width, int screen_height, GLFWwindow* window)
BaseCameraClass::BaseCameraClass(int screen_width, int screen_height)
{
    //	float yaw = 180.0f; // blender
    //	float pitch = 16.0f; // blender


    glm::vec3 cameraPos = glm::vec3(-0.222370f, -0.661427f, 5.455092f);
    // 
    //yaw: 186.096832, pitch : 16.499952, camera.x : 5.760163, camera.y : -4.602411, camera.z : 1.775038
    //glm::vec3 cameraPos = glm::vec3(5.760163f, -4.602411f, 1.775038f); // blender

//	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // firstMouse = true;
    Mouse_first_frame = true;
    Mouse_lastX = (float)screen_width / 2.0;
    Mouse_lastY = (float)screen_height / 2.0;



    float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    //float yaw = -180.0f;
    float pitch = -10.0f;

    camera_fov = 45.0f;
    //camera_yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    // 
    camera_yaw = yaw;
    //float yaw = -180.0f;
    camera_pitch = pitch;

    camera_up = cameraUp;
    camera_position = cameraPos;
    //camera_right = 


    movement_speed = SPEED;


    m_screen_width = screen_width;
    m_screen_height = screen_height;;


    //	main_glfw3_window = window;


    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(front);

    camera_projection = glm::perspective(glm::radians(camera_fov), (float)screen_width / (float)screen_height, 0.1f, 100.0f);
    camera_view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
}


BaseCameraClass::~BaseCameraClass()
{



}

glm::mat4   BaseCameraClass::GetViewMatrix() const {

    return camera_view;


}// GetViewMatrix() {}; //: Returns the glm::mat4 view matrix.


glm::mat4   BaseCameraClass::GetProjectionMatrix() {
    return camera_projection;
} //: Returns the glm::mat4 projection matrix.

void BaseCameraClass::ProcessKeyboard(camera_movement_t direction, float delta_time) {
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

void BaseCameraClass::ProcessMouseMovement(float xpos, float ypos, float clamppitch) {
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
}// : A virtual function for handling mouse movement.

void BaseCameraClass::ProcessMouseScroll(float yscroll) {

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
