#ifndef ADD_INTERSECTION_CUBE_H
#define ADD_INTERSECTION_CUBE_H


#ifdef WIN32
#pragma once
#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>


//int AddCubeLine(glm::vec3 startPos, glm::vec3 endPos, float width, glm::vec4 rayColor);


//int AddCubeLine2(glm::vec3 startPos, glm::vec3 direction, float width, glm::vec4 rayColor);
int AddIntersectionCube(float x, float y, float z, float width);

int AddIntersectionCube2(float x, float y, float z, float width);



#endif