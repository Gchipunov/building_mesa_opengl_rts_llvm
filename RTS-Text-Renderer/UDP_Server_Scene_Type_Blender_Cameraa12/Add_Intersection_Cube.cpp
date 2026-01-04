
#include "Add_Intersection_Cube.h"


extern std::vector<float> mainVertices;
extern GLuint VAO;

extern GLuint VBO;

// human prototype original

int AddIntersectionCube(float x, float y, float z, float width)

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
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //   width, -width, -width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(1.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);



    //   width,  width, -width,  1.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(1.0f);  mainVertices.push_back(1.0f); mainVertices.push_back(66.0f);

    // triangle 1
 //   width,  width, -width,  1.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // -width,  width, -width,  0.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // -width, -width, -width,  0.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // face 1
// triangle 2
// -width, -width,  width,  0.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //  width, -width,  width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //  width,  width,  width,  1.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // triangle 3
    // width,  width,  width,  1.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);


    //-width,  width,  width,  0.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //-width, -width,  width,  0.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //face 2
 // triangle 4
//-width,  width,  width,  1.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //-width,  width, -width,  1.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //-width, -width, -width,  0.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // triangle 5
//-width, -width, -width,  0.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //-width, -width,  width,  0.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //-width,  width,  width,  1.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //face 3
    // triangle 6

// width,  width,  width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // width,  width, -width,  1.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);


    // width, -width, -width,  0.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // triangle 7
// width, -width, -width,  0.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //  width, -width,  width,  0.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //   width,  width,  width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //face 4
    // triangle 8
//  -width, -width, -width,  0.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // width, -width, -width,  1.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //width, -width,  width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // triangle 9

//    width, -width,  width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // -width, -width,  width,  0.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // -width, -width, -width,  0.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(-width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //face 5
    //triangle 10
// -width,  width, -width,  0.0f, 1.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //  width,  width, -width,  1.0f, 1.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    //  width,  width,  width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);
    //triangle 11
//  width,  width,  width,  1.0f, 0.0f,
    mainVertices.push_back(width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // -width,  width,  width,  0.0f, 0.0f,
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // -width,  width, -width,  0.0f, 1.0f
    mainVertices.push_back(-width + x);  mainVertices.push_back(width + y);  mainVertices.push_back(-width + z); mainVertices.push_back(0.0f);  mainVertices.push_back(0.0f); mainVertices.push_back(66.0f);

    // };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data() );
    GLenum err = glGetError(); if (err != GL_NO_ERROR) {
        printf("OpenGL Error: %x\n", err);
        exit(9);
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


/**
 * @brief Adds a cube to the mainVertices vector with position, UVs, and a shader type.
 *
 * This function generates all 36 vertices (12 triangles) for a cube centered at
 * (x, y, z) with a given width. Each vertex has 6 attributes:
 * - Position (x, y, z)
 * - UV Coordinates (u, v)
 * - Shader Type (66.0f)
 *
 * @param x The x-position of the center of the cube.
 * @param y The y-position of the center of the cube.
 * @param z The z-position of the center of the cube.
 * @param width The full width of the cube (half-width is used for calculations).
 * @return The total number of vertices added (36).
 */
int AddIntersectionCube2(float x, float y, float z, float width)
{
    // The half-width of the cube for easier calculations
    float halfWidth = width / 2.0f;
    const float SHADER_TYPE_66 = 66.0f;

    // Define the 8 vertices of the cube first for clarity.
    // Each vertex is a glm::vec3
    glm::vec3 v1(-halfWidth, -halfWidth, -halfWidth); // -x, -y, -z
    glm::vec3 v2(halfWidth, -halfWidth, -halfWidth); // +x, -y, -z
    glm::vec3 v3(halfWidth, halfWidth, -halfWidth); // +x, +y, -z
    glm::vec3 v4(-halfWidth, halfWidth, -halfWidth); // -x, +y, -z

    glm::vec3 v5(-halfWidth, -halfWidth, halfWidth); // -x, -y, +z
    glm::vec3 v6(halfWidth, -halfWidth, halfWidth); // +x, -y, +z
    glm::vec3 v7(halfWidth, halfWidth, halfWidth); // +x, +y, +z
    glm::vec3 v8(-halfWidth, halfWidth, halfWidth); // -x, +y, +z

    // Add the center offset to all vertices
    glm::vec3 offset(x, y, z);
    v1 += offset; v2 += offset; v3 += offset; v4 += offset;
    v5 += offset; v6 += offset; v7 += offset; v8 += offset;

    // A helper macro to push a vertex with its UVs and type
#define PUSH_VERTEX(v_vec, u_val, v_val, type_val) \
        mainVertices.push_back((v_vec).x); \
        mainVertices.push_back((v_vec).y); \
        mainVertices.push_back((v_vec).z); \
        mainVertices.push_back(u_val); \
        mainVertices.push_back(v_val); \
        mainVertices.push_back(type_val);

    // Now, define the 12 triangles using the vertices and correct UVs.
    // The UVs are assigned to each face separately.

    // ----------------------------------------------------
    // Front face (-z plane)
    // ----------------------------------------------------
    // Triangle 1: v1, v2, v3 (UVs: 0,0 | 1,0 | 1,1)
    PUSH_VERTEX(v1, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v2, 1.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v3, 1.0f, 1.0f, SHADER_TYPE_66);
    // Triangle 2: v1, v3, v4 (UVs: 0,0 | 1,1 | 0,1)
    PUSH_VERTEX(v1, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v3, 1.0f, 1.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v4, 0.0f, 1.0f, SHADER_TYPE_66);

    // ----------------------------------------------------
    // Back face (+z plane)
    // ----------------------------------------------------
    // Triangle 3: v5, v7, v6 (UVs: 0,0 | 1,1 | 1,0)
    PUSH_VERTEX(v5, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v7, 1.0f, 1.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v6, 1.0f, 0.0f, SHADER_TYPE_66);
    // Triangle 4: v5, v8, v7 (UVs: 0,0 | 0,1 | 1,1)
    PUSH_VERTEX(v5, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v8, 0.0f, 1.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v7, 1.0f, 1.0f, SHADER_TYPE_66);

    // ----------------------------------------------------
    // Left face (-x plane)
    // ----------------------------------------------------
    // Triangle 5: v1, v4, v8 (UVs: 0,0 | 1,0 | 1,1)
    PUSH_VERTEX(v1, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v4, 1.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v8, 1.0f, 1.0f, SHADER_TYPE_66);
    // Triangle 6: v1, v8, v5 (UVs: 0,0 | 1,1 | 0,1)
    PUSH_VERTEX(v1, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v8, 1.0f, 1.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v5, 0.0f, 1.0f, SHADER_TYPE_66);

    // ----------------------------------------------------
    // Right face (+x plane)
    // ----------------------------------------------------
    // Triangle 7: v2, v6, v7 (UVs: 0,0 | 1,0 | 1,1)
    PUSH_VERTEX(v2, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v6, 1.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v7, 1.0f, 1.0f, SHADER_TYPE_66);
    // Triangle 8: v2, v7, v3 (UVs: 0,0 | 1,1 | 0,1)
    PUSH_VERTEX(v2, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v7, 1.0f, 1.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v3, 0.0f, 1.0f, SHADER_TYPE_66);

    // ----------------------------------------------------
    // Top face (+y plane)
    // ----------------------------------------------------
    // Triangle 9: v4, v3, v7 (UVs: 0,0 | 1,0 | 1,1)
    PUSH_VERTEX(v4, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v3, 1.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v7, 1.0f, 1.0f, SHADER_TYPE_66);
    // Triangle 10: v4, v7, v8 (UVs: 0,0 | 1,1 | 0,1)
    PUSH_VERTEX(v4, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v7, 1.0f, 1.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v8, 0.0f, 1.0f, SHADER_TYPE_66);

    // ----------------------------------------------------
    // Bottom face (-y plane)
    // ----------------------------------------------------
    // Triangle 11: v1, v5, v6 (UVs: 0,0 | 1,0 | 1,1)
    PUSH_VERTEX(v1, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v5, 1.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v6, 1.0f, 1.0f, SHADER_TYPE_66);
    // Triangle 12: v1, v6, v2 (UVs: 0,0 | 1,1 | 0,1)
    PUSH_VERTEX(v1, 0.0f, 0.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v6, 1.0f, 1.0f, SHADER_TYPE_66);
    PUSH_VERTEX(v2, 0.0f, 1.0f, SHADER_TYPE_66);

    // After adding all vertices, update the VBO data.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("OpenGL Error: %x\n", err);
    }

    // Ensure the vertex attribute pointers are correctly configured
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // The UVs and type are a vec3 starting at the 4th element (index 3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind to prevent accidental changes
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 36;
}
