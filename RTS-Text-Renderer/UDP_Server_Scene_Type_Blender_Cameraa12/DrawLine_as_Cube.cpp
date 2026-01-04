
#include "DrawLine_as_Cube.h"


extern std::vector<float> mainVertices;
extern GLuint VAO;

extern GLuint VBO;

// human prototype original
/*
int AddCubeLine(glm::vec3 startPos, glm::vec3 endPos, float width, glm::vec4 rayColor)

//int AddCube(float x, float y, float z)
{

  ////  Cube* newCube = (Cube*)malloc(sizeof(Cube));

  ////  newCube->halfSize = 0.5f;
 ////   newCube->position.x = x;
 ////   newCube->position.y = y;
////    newCube->position.z = z;

 ////   newCube->velocity.x = 0.0f;
 ////   newCube->velocity.y = 0.0f;
 ////   newCube->velocity.z = 0.0f;
 ////   newCube->iRenderType = 1;

    // vvtype seems not to exist like this allocation with malloc.
   //// newCube->vvtype.push_back(33.0f); // kinda like what happens when gc_sdk client is not initialize inventory in TF2 Source1 SDK
 ////   newCube->vvtype.


  ////  cubes.push_back(*newCube);

    // Create a temporary Cube object on the stack

   /////// Cube newCube;

   ////// newCube.halfSize = 0.5f;
  ////////  newCube.position.x = x;
  ///////  newCube.position.y = y;
  ///////  newCube.position.z = z;

   //////// newCube.velocity.x = 0.0f;
  ///////  newCube.velocity.y = 0.0f;
   /////// newCube.velocity.z = 0.0f;
  ///////  newCube.iRenderType = 1;

    // The vector is automatically constructed here
   /////// newCube.vvtype.push_back(33.0f);

    // Push a copy of the temporary object into the vector
  //////  cubes.push_back(newCube);

    // The temporary 'newCube' object is automatically destroyed when it goes out of scope.
    // The vector 'cubes' now holds its own copy.



    // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
   // float vertices[] = {
   // -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
   // // face 0
       // triangle 0
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(1.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);



    //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(1.0f);  mainVertices.push_back(1.0f); mainVertices.push_back(33.0f);

    // triangle 1
 //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // face 1
// triangle 2
// -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 3
    // 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);


    //-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 2
 // triangle 4
//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 5
//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 3
    // triangle 6

// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);


    // 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 7
// 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 4
    // triangle 8
//  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 9

//    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 5
    //triangle 10
// -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);
    //triangle 11
//  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
    GLenum err = glGetError(); if (err != GL_NO_ERROR) {
        printf("OpenGL Error: %x\n", err);
        exit(0);
    }

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 36;
}
*/

/**
 * @brief Generates and adds vertices for a cuboid (line with width) to a global vertex buffer.
 *
 * This function calculates the geometry for a cuboid aligned with the vector from startPos to endPos.
 * It generates 12 triangles (36 vertices) to represent the cuboid's 6 faces and pushes them
 * into a global 'mainVertices' vector. After adding the vertices, it updates the OpenGL
 * VBO to contain the new data.
 *
 * @param startPos The starting point of the line.
 * @param endPos The ending point of the line.
 * @param width The width and height of the line's cross-section.
 * @param rayColor The color to apply to all vertices of the line.
 * @return The number of vertices added (36 for a complete cuboid).
 */

int AddCubeLine(glm::vec3 startPos, glm::vec3 endPos, float width, glm::vec4 rayColor)
{

    return 0;
}


int AddCubeLine2(glm::vec3 startPos, glm::vec3 direction, float width, glm::vec4 rayColor)
{

    // C++
   // Calculate the end position from the start position and direction vector.
   // This is the key line to add.
   // glm::vec3 endPos = startPos + direction;

    float scaleFactor = 3.0f;
    glm::vec3 scaledVector = direction * scaleFactor;

    //  glm::vec3 endPos = startPos + direction;
    glm::vec3 endPos = startPos + scaledVector;

    //float length = glm::length(direction);
    float length = glm::length(scaledVector);

    // If the length is close to zero, there's nothing to draw.
    if (length < 0.0001f) {
        return 0;
    }

    // Normalize the direction vector
// glm::vec3 normalized_dir = direction / length;
    glm::vec3 normalized_dir = scaledVector / length;


    // Find two orthogonal vectors to form the cross-section plane
    glm::vec3 right, up;
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Handle the case where the line is vertical
    if (std::abs(glm::dot(normalized_dir, world_up)) > 0.999f) {
        right = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else {
        right = glm::normalize(glm::cross(normalized_dir, world_up));
    }
    up = glm::normalize(glm::cross(right, normalized_dir));

    // Calculate the half-width for ease of use
    float half_width = width * 0.5f;

    // Calculate the 8 vertices of the cuboid
    // Four vertices at the start position
    glm::vec3 p1 = startPos - up * half_width + right * half_width;
    glm::vec3 p2 = startPos + up * half_width + right * half_width;
    glm::vec3 p3 = startPos - up * half_width - right * half_width;
    glm::vec3 p4 = startPos + up * half_width - right * half_width;

    // Four vertices at the end position
    glm::vec3 p5 = endPos - up * half_width + right * half_width;
    glm::vec3 p6 = endPos + up * half_width + right * half_width;
    glm::vec3 p7 = endPos - up * half_width - right * half_width;
    glm::vec3 p8 = endPos + up * half_width - right * half_width;

    rayColor.r = 0.0f;
    rayColor.g = 0.0f;
    rayColor.b = 55.0f;



    // This is the 'type' value you want to pass to the shader.
  // We will use this in the rayColor.b component.
    float shaderType = rayColor.b;

    // Now, define the 12 triangles (6 faces, 2 triangles per face) using these 8 vertices.
    // For each vertex, we will add its position (3 floats) and its UV + type (3 floats).
    // The UV coordinates are the most important part of this update.

    // ----------------------------------------------------
    // Face 1: Front face (p1, p3, p4, p1, p4, p2)
    // ----------------------------------------------------
    // Triangle 1: p1, p3, p4
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 1.0f, 1.0f, shaderType });

    // Triangle 2: p1, p4, p2
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 0.0f, 1.0f, shaderType });

    // ----------------------------------------------------
    // Face 2: Back face (p5, p6, p8, p5, p8, p7)
    // ----------------------------------------------------
    // Triangle 3: p5, p6, p8
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 0.0f, 1.0f, shaderType });

    // Triangle 4: p5, p8, p7
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 0.0f, 0.0f, shaderType });


    // ----------------------------------------------------
    // Face 3: Right face (p3, p7, p8, p3, p8, p4)
    // ----------------------------------------------------
    // Triangle 5: p3, p7, p8
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 1.0f, shaderType });

    // Triangle 6: p3, p8, p4
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 0.0f, 1.0f, shaderType });

    // ----------------------------------------------------
    // Face 4: Left face (p1, p2, p6, p1, p6, p5)
    // ----------------------------------------------------
    // Triangle 7: p1, p2, p6
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 0.0f, 1.0f, shaderType });

    // Triangle 8: p1, p6, p5
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 0.0f, 0.0f, shaderType });

    // ----------------------------------------------------
    // Face 5: Top face (p2, p4, p8, p2, p8, p6)
    // ----------------------------------------------------
    // Triangle 9: p2, p4, p8
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 0.0f, shaderType });

    // Triangle 10: p2, p8, p6
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 0.0f, 0.0f, shaderType });

    // ----------------------------------------------------
    // Face 6: Bottom face (p1, p5, p7, p1, p7, p3)
    // ----------------------------------------------------
    // Triangle 11: p1, p5, p7
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 1.0f, 1.0f, shaderType });

    // Triangle 12: p1, p7, p3
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 0.0f, 1.0f, shaderType });

    /*
    *
    *
    // Now, define the 12 triangles (6 faces, 2 triangles per face) using these 8 vertices.
 // Face 1: startPos face (p1, p2, p3, p4)
   // mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    rayColor.r = 1.0f;
    rayColor.g = 0.0f;
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 2: endPos face (p5, p6, p7, p8)
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 3: Top face (p2, p6, p4, p8)
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 4: Bottom face (p1, p5, p3, p7)
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 5: Left face (p1, p2, p5, p6)
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 6: Right face (p3, p4, p7, p8)
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    */

    /*
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(1.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);



    //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(1.0f);  mainVertices.push_back(1.0f); mainVertices.push_back(33.0f);

    // triangle 1
 //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // face 1
// triangle 2
// -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 3
    // 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);


    //-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 2
 // triangle 4
//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 5
//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 3
    // triangle 6

// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);


    // 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 7
// 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 4
    // triangle 8
//  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 9

//    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 5
    //triangle 10
// -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);
    //triangle 11
//  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);
    */
    // };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
    GLenum err = glGetError(); if (err != GL_NO_ERROR) {
        printf("OpenGL Error: %x\n", err);
        exit(6);
    }

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 36;

}


int AddCubeLine3(glm::vec3 startPos, glm::vec3 direction, float width, glm::vec4 rayColor, float distance)
{

    // C++
   // Calculate the end position from the start position and direction vector.
   // This is the key line to add.
   // glm::vec3 endPos = startPos + direction;

   // float scaleFactor = 3.0f;
    glm::vec3 scaledVector = direction * distance;

    //  glm::vec3 endPos = startPos + direction;
    glm::vec3 endPos = startPos + scaledVector;

    //float length = glm::length(direction);
    float length = glm::length(scaledVector);

    // If the length is close to zero, there's nothing to draw.
    if (length < 0.0001f) {
        return 0;
    }

    // Normalize the direction vector
// glm::vec3 normalized_dir = direction / length;
    glm::vec3 normalized_dir = scaledVector / length;


    // Find two orthogonal vectors to form the cross-section plane
    glm::vec3 right, up;
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Handle the case where the line is vertical
    if (std::abs(glm::dot(normalized_dir, world_up)) > 0.999f) {
        right = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else {
        right = glm::normalize(glm::cross(normalized_dir, world_up));
    }
    up = glm::normalize(glm::cross(right, normalized_dir));

    // Calculate the half-width for ease of use
    float half_width = width * 0.5f;

    // Calculate the 8 vertices of the cuboid
    // Four vertices at the start position
    glm::vec3 p1 = startPos - up * half_width + right * half_width;
    glm::vec3 p2 = startPos + up * half_width + right * half_width;
    glm::vec3 p3 = startPos - up * half_width - right * half_width;
    glm::vec3 p4 = startPos + up * half_width - right * half_width;

    // Four vertices at the end position
    glm::vec3 p5 = endPos - up * half_width + right * half_width;
    glm::vec3 p6 = endPos + up * half_width + right * half_width;
    glm::vec3 p7 = endPos - up * half_width - right * half_width;
    glm::vec3 p8 = endPos + up * half_width - right * half_width;

    rayColor.r = 0.0f;
    rayColor.g = 0.0f;
    rayColor.b = 56.0f;



    // This is the 'type' value you want to pass to the shader.
  // We will use this in the rayColor.b component.
    float shaderType = rayColor.b;

    // Now, define the 12 triangles (6 faces, 2 triangles per face) using these 8 vertices.
    // For each vertex, we will add its position (3 floats) and its UV + type (3 floats).
    // The UV coordinates are the most important part of this update.

    // ----------------------------------------------------
    // Face 1: Front face (p1, p3, p4, p1, p4, p2)
    // ----------------------------------------------------
    // Triangle 1: p1, p3, p4
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 1.0f, 1.0f, shaderType });

    // Triangle 2: p1, p4, p2
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 0.0f, 1.0f, shaderType });

    // ----------------------------------------------------
    // Face 2: Back face (p5, p6, p8, p5, p8, p7)
    // ----------------------------------------------------
    // Triangle 3: p5, p6, p8
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 0.0f, 1.0f, shaderType });

    // Triangle 4: p5, p8, p7
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 0.0f, 0.0f, shaderType });


    // ----------------------------------------------------
    // Face 3: Right face (p3, p7, p8, p3, p8, p4)
    // ----------------------------------------------------
    // Triangle 5: p3, p7, p8
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 1.0f, shaderType });

    // Triangle 6: p3, p8, p4
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 0.0f, 1.0f, shaderType });

    // ----------------------------------------------------
    // Face 4: Left face (p1, p2, p6, p1, p6, p5)
    // ----------------------------------------------------
    // Triangle 7: p1, p2, p6
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 0.0f, 1.0f, shaderType });

    // Triangle 8: p1, p6, p5
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 0.0f, 0.0f, shaderType });

    // ----------------------------------------------------
    // Face 5: Top face (p2, p4, p8, p2, p8, p6)
    // ----------------------------------------------------
    // Triangle 9: p2, p4, p8
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 0.0f, shaderType });

    // Triangle 10: p2, p8, p6
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, 0.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, 0.0f, 0.0f, shaderType });

    // ----------------------------------------------------
    // Face 6: Bottom face (p1, p5, p7, p1, p7, p3)
    // ----------------------------------------------------
    // Triangle 11: p1, p5, p7
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, 1.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 1.0f, 1.0f, shaderType });

    // Triangle 12: p1, p7, p3
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, 0.0f, 0.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, 1.0f, 1.0f, shaderType });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, 0.0f, 1.0f, shaderType });

    /*
    *
    *
    // Now, define the 12 triangles (6 faces, 2 triangles per face) using these 8 vertices.
 // Face 1: startPos face (p1, p2, p3, p4)
   // mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    rayColor.r = 1.0f;
    rayColor.g = 0.0f;
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 2: endPos face (p5, p6, p7, p8)
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 3: Top face (p2, p6, p4, p8)
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 4: Bottom face (p1, p5, p3, p7)
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 5: Left face (p1, p2, p5, p6)
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b });

    // Face 6: Right face (p3, p4, p7, p8)
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b });
    */

    /*
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(1.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);



    //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(1.0f);  mainVertices.push_back(1.0f); mainVertices.push_back(33.0f);

    // triangle 1
 //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // face 1
// triangle 2
// -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 3
    // 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);


    //-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 2
 // triangle 4
//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 5
//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 3
    // triangle 6

// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);


    // 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 7
// 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 4
    // triangle 8
//  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // triangle 9

//    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(-0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //face 5
    //triangle 10
// -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);
    //triangle 11
//  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    mainVertices.push_back(0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);

    // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    mainVertices.push_back(-0.5f + x);  mainVertices.push_back(0.5f + y);  mainVertices.push_back(-0.5f + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);
    */
    // };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
    GLenum err = glGetError(); if (err != GL_NO_ERROR) {
        printf("OpenGL Error: %x\n", err);
        exit(0);
    }

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 36;

}
// https://gemini.google.com/app/c8360db18827378d
// find in C++ in this code, whats wrong that gives all the cubes a impulse if one cube is intersected by a ray cast:

//if (button == GLFW_MOUSE_BUTTON_4 && action == GLFW_PRESS) {


int AddCubeLineLOL(glm::vec3 startPos, glm::vec3 endPos, float width, glm::vec4 rayColor)
{
    // The user's original code adds 6 floats per vertex (position, texCoords/type).
    // This implementation assumes a vertex format of 3 floats for position and 4 floats for color.
    // This is a reasonable assumption given the 'glm::vec4 rayColor' parameter.
    // We will update the glVertexAttribPointer calls accordingly.

    // Clear previous data for a fresh start (optional, depending on your application logic)
  //  mainVertices.clear();

    // Calculate the direction vector and length of the line
    glm::vec3 dir = endPos - startPos;
    float length = glm::length(dir);

    // If the length is close to zero, there's nothing to draw.
    if (length < 0.0001f) {
        return 0;
    }

    // Normalize the direction vector
    glm::vec3 normalized_dir = dir / length;

    // Find two orthogonal vectors to form the cross-section plane
    glm::vec3 right, up;
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Handle the case where the line is vertical
    if (std::abs(glm::dot(normalized_dir, world_up)) > 0.999f) {
        right = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else {
        right = glm::normalize(glm::cross(normalized_dir, world_up));
    }
    up = glm::normalize(glm::cross(right, normalized_dir));

    // Calculate the half-width for ease of use
    float half_width = width * 0.5f;

    // Calculate the 8 vertices of the cuboid
    // Four vertices at the start position
    glm::vec3 p1 = startPos - up * half_width + right * half_width;
    glm::vec3 p2 = startPos + up * half_width + right * half_width;
    glm::vec3 p3 = startPos - up * half_width - right * half_width;
    glm::vec3 p4 = startPos + up * half_width - right * half_width;

    // Four vertices at the end position
    glm::vec3 p5 = endPos - up * half_width + right * half_width;
    glm::vec3 p6 = endPos + up * half_width + right * half_width;
    glm::vec3 p7 = endPos - up * half_width - right * half_width;
    glm::vec3 p8 = endPos + up * half_width - right * half_width;

    // Now, define the 12 triangles (6 faces, 2 triangles per face) using these 8 vertices.
    // Face 1: startPos face (p1, p2, p3, p4)
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });

    // Face 2: endPos face (p5, p6, p7, p8)
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });

    // Face 3: Top face (p2, p6, p4, p8)
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });

    // Face 4: Bottom face (p1, p5, p3, p7)
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });

    // Face 5: Left face (p1, p2, p5, p6)
    mainVertices.insert(mainVertices.end(), { p1.x, p1.y, p1.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p2.x, p2.y, p2.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p6.x, p6.y, p6.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p5.x, p5.y, p5.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });

    // Face 6: Right face (p3, p4, p7, p8)
    mainVertices.insert(mainVertices.end(), { p3.x, p3.y, p3.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p4.x, p4.y, p4.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p8.x, p8.y, p8.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });
    mainVertices.insert(mainVertices.end(), { p7.x, p7.y, p7.z, rayColor.r, rayColor.g, rayColor.b, rayColor.a });

    // Now, update the OpenGL VBO with the new data.
    // This part of the code is taken directly from your provided snippet.
    // Note: Calling glBufferData every time is inefficient for real-time applications,
    // but it's consistent with your original code.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        //  std::cerr << "OpenGL Error: " << err << std::endl;
        printf("OpenGL err:%d", err);

        exit(1);
    }

    // Update the vertex attribute pointers to match the new vertex format (3 pos, 4 color)
    // The stride is now 7 floats (3 for position + 4 for color)
    // position attribute (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute (location 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Return the number of vertices for a complete cuboid
    return 36;
}

