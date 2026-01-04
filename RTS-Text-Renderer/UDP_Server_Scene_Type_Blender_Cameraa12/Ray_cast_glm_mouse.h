
#ifndef RAY_CAST_GLM_MOUSE
#define RAY_CAST_GLM_MOUSE


#ifdef WIN32
#pragma once
#endif
#define GLM_ENABLE_EXPERIMENTAL


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <glm/gtx/intersect.hpp>


// Define a ray structure using glm::vec3
struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
};



/**
 * @brief Creates a ray from 2D mouse coordinates in screen space.
 * * This function uses glm::unProject to efficiently convert mouse coordinates
 * into a ray in world space. The process involves two unprojections: one for
 * the near plane and one for the far plane, which are then used to calculate
 * the ray's origin and direction.
 *
 * @param mouse_x The x-coordinate of the mouse in screen space (e.g., pixels).
 * @param mouse_y The y-coordinate of the mouse in screen space (e.g., pixels).
 * @param screen_width The width of the viewport.
 * @param screen_height The height of the viewport.
 * @param view_matrix The camera's view matrix.
 * @param projection_matrix The projection matrix (perspective or orthographic).
 * @return A Ray structure containing the origin and normalized direction.
 */
Ray create_ray_from_mouse(
    int mouse_x, int mouse_y, int screen_width, int screen_height,
    const glm::mat4& view_matrix, const glm::mat4& projection_matrix);


// create_ray_from_mouse_normalized
Ray create_ray_from_mouse_normalized(
    float virtual_mouse_x, int virtual_mouse_y, int screen_width, int screen_height,
    const glm::mat4& view_matrix, const glm::mat4& projection_matrix);

Ray create_ray_from_mouse_unproject(
    int mouse_x, int mouse_y, int screen_width, int screen_height,
    const glm::mat4& view_matrix, const glm::mat4& projection_matrix);

glm::vec2 checkMouseClick(Ray my_ray,
    glm::vec3 v0,//(-1.0f, -1.0f, 0.0f),
    glm::vec3 v1,//(1.0f, -1.0f, 0.0f),
    glm::vec3 v2//(0.0f, 1.0f, 0.0f)
);


glm::vec2 checkMouseClick2(Ray my_ray,
    glm::vec3 v0,//(-1.0f, -1.0f, 0.0f),
    glm::vec3 v1,//(1.0f, -1.0f, 0.0f),
    glm::vec3 v2,//(0.0f, 1.0f, 0.0f)
    bool& Didhit,
    float& t2
);
#endif