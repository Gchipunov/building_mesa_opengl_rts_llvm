// https://github.com/NCCA/Camera
//#include <glad/glad.h>
#define GLEW_STATIC
#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
#include <GLFW/glfw3.h>


//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <learnopengl/shader_m.h>
#include "shader_m.h"

#include <vector>
//#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "UDPClient_update-AABB-Cubes.h"
#include "UDPClient_update_data_Cubes.h"
//#include  "Blender-OpenGL-Camera.h"
#include "Base-Camera-Class.h"
#include "Blender-Camera-Class.h"
#include "QuatCamera.h"
#include "Ray_cast_glm_mouse.h"
#include "DrawLine_as_Cube.h"
#include "Add_Intersection_Cube.h"
#include "Cursor_UI_Draw.h"

#include "common_multiplayer5.h"

//#include "UDP_Client_Replication.h"

// #include "TCP_Client_Replication.h"

#include "UDP_Client_Class.h"
#include "UDP_Client_Graphics_Layer.h"

#include "Intmain_Curl.h"
#include "MainMenu_UI.h"
#include "GameHUD_UI.h"
#include "ANA_GameState.h"

#include "BuildStructure_Cube.h"

#include "Terrian_GridPlane.h"

#include "Texture_Sprite_Altas_Loader.h"

// add rotation aabb
// //add objects by shader type vvtype
// add transparent ground

// main code: https://docs.google.com/document/d/1mhUuG0jsBPZvGCispnBLEuKR54J6O-TIibpvoD8nZAg/edit?tab=t.0
// 
// https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.4.camera_class/camera_class.cpp
// ray cast: https://www.programmingcreatively.com/ray-casting-mouse-picking.php
// click ing on objects: https://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/



// https://www.youtube.com/watch?v=GCnipL4T0Ho



glm::vec3 g_triangleVertice1 = glm::vec3(1.5, 1.5, 1.5f);
glm::vec3 g_triangleVertice2 = glm::vec3(1.5, -1.5, 1.5f);
glm::vec3 g_triangleVertice3 = glm::vec3(.75, 0.0f, 1.5f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


void processInput(GLFWwindow* window);

// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
unsigned int g_Width = 800;
unsigned int  g_Height = 600;



int iNumVertexAttributes = 6;

int iUniformsRenderType = 1;

int iConnected = 0;
int iFirstConnect = 0;

unsigned int iNumTrianglesDraw = 54;

GLuint texture5 = -1;//unsigned int texture5;

GLuint texture6 = -1;//unsigned int texture5;


unsigned int VBO, VAO;

// Time
float deltaTime = 0.0f;
float lastFrame = 0.0f;


// camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

//glm::vec3 cameraPos = glm::vec3(7.35f, -6.92, 4.95f);

//glm::vec3 cameraPos = glm::vec3(5.0f,  -5.0f, 3.0f);
//yaw: -93.800102, pitch: -10.300071, camera.x: -0.222370, camera.y: -0.661427, camera.z: 5.455092
glm::vec3 cameraPos = glm::vec3(-0.222370f, -0.661427f, 5.455092f);
// 
//yaw: 186.096832, pitch : 16.499952, camera.x : 5.760163, camera.y : -4.602411, camera.z : 1.775038
//glm::vec3 cameraPos = glm::vec3(5.760163f, -4.602411f, 1.775038f); // blender

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float yaw = -180.0f;
float pitch = -10.0f;
// 
//float yaw = 63.0f;  // Set initial yaw to 63.0   , from blender and bard
//float pitch = 46.96f; // Set initial pitch to 46.96 , from blender and bard

//glm::vec3 cameraFront = glm::vec3(0.0f, 1.0f, 0.0f); // blender
//glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, 1.0f); // blender

//float yaw = 180.0f; // blender
//float pitch = 16.0f; // blender

float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
//float deltaTime = 0.0f;	// time between current frame and last frame
//float lastFrame = 0.0f;

std::vector <float> mainVertices;


//BlenderOpenGLCameraClass* blendercamera;
BaseCameraClass* basecamera;
BlenderCameraClass* blendercamera;
BlenderCameraClass2* blendercamera2;
BlenderCameraClass3* blendercamera3;
BlenderCameraClass4* blendercamera4;
BlenderCameraClass5* blendercamera5;
BlenderCameraClass6* blendercamera6;
BlenderCameraClass7* blendercamera7;

//ColoQuatCamera* g_ColoQuatCamera;
ColoQuatCamera* quatcamera;

Cursor_UI_Draw* cursor_ui_draw;

int iTypeCamera = 4;



int AddCube(float x, float y, float z)
{
    /*
    Cube* newCube = (Cube*)malloc(sizeof(Cube));

    newCube->halfSize = 0.5f;
    newCube->position.x = x;
    newCube->position.y = y;
    newCube->position.z = z;

    newCube->velocity.x = 0.0f;
    newCube->velocity.y = 0.0f;
    newCube->velocity.z = 0.0f;
    newCube->iRenderType = 1;

    // vvtype seems not to exist like this allocation with malloc.
   // newCube->vvtype.push_back(33.0f); // kinda like what happens when gc_sdk client is not initialize inventory in TF2 Source1 SDK
 //   newCube->vvtype.


    cubes.push_back(*newCube);
    */
    // Create a temporary Cube object on the stack
    Cube newCube;

    newCube.halfSize = 0.5f;
    newCube.position.x = x;
    newCube.position.y = y;
    newCube.position.z = z;

    newCube.velocity.x = 0.0f;
    newCube.velocity.y = 0.0f;
    newCube.velocity.z = 0.0f;
    newCube.iRenderType = 1;

    // The vector is automatically constructed here
  //  newCube.vvtype.push_back(33.0f);
    newCube.iHighLight[0] = 33;
    newCube.iHighLight[1] = 34;
    newCube.iHighLight[2] = 35;
    newCube.iHighLight[3] = 36;



    // Push a copy of the temporary object into the vector
    cubes.push_back(newCube);

    CubeGraphicsData newCubeGraphicsData;
    newCubeGraphicsData.mainVerticesIndex = mainVertices.size();
    cubeGraphicsData.push_back(newCubeGraphicsData);

    // mainVerticesIndex


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
        exit(5);
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





// Helper function to print a glm::mat4 matrix to the console.
// This function assumes the matrix is column-major (the OpenGL default)
// and prints it in a more human-readable row-major format.
void printMat4(const glm::mat4& matrix) {
    printf("Matrix (4x4):\n");
    for (int i = 0; i < 4; ++i) {
        printf("| %6.2f %6.2f %6.2f %6.2f |\n",
            matrix[0][i], matrix[1][i], matrix[2][i], matrix[3][i]);
    }
    printf("\n");
}

// Time Calculation Our way to see what the time change was between last render and phyiscs or disabled physics frame
void renderTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // copy mutex UDP data
}
bool g_bChangedResizeMainWindow = true;
int g_mouse_button = 0;
int g_mouse_action = 0;
int g_mouse_mods = 0;
int g_iFrame = 0;


void updateRealTimeUniforms(Shader& ourShader)
{
    ourShader.setInt("iFrame", g_iFrame++);
    ourShader.setFloat("iTime", (float)glfwGetTime());
    if (g_bChangedResizeMainWindow)
    {
        //  ourShader.setVec2("iResolution", g_Width, g_Height);
        ourShader.setVec3("iResolution", 1.0f, 1.0f, 1.0f);   //most shader toy shaders 1.0 is being past in
        g_bChangedResizeMainWindow = false;
    }

    if (cursor_ui_draw)
    {
        // int g_mouse_button = 0;
        // int g_mouse_action = 0;
        // int g_mouse_mods = 0;
          //float mod_encode = g_mouse_mods * 100.0f;

        ourShader.setVec4("iMouse", cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY, (float)g_mouse_button, (float)g_mouse_action);


    }
}

int main(int argc, char** argv)
{
    mainGetIntmainCloud_ANA(); // if OpenGL doesn't initize to OpenGL 3.3 or 3.0 then need to report it to curl Cloud
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(g_Width, g_Height, "intmain.in RTS-Engine UDP_Server_Scene_Type_Blender_Camera10 - Camera Class - Types Blender Color, Press Left Shift to Ray Cast ", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // 
     // glad: load all OpenGL function pointers
     // ---------------------------------------
     //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
     //    std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    printf("glewInit\n\n");
    glewInit();

    g_pAnaGameState = new AnaGameState();

    g_ANA_MainMenuUI = new MainMenuUI();
    g_ANA_GameHUDUI = new GameHUDUI();

    g_pGoshaRayIntersectionPlaneManager = new GoshaRayIntersectionPlaneManager();

    // -------------Blender Camera------------- //
    ///========================================
  //  blendercamera = new BlenderOpenGLCameraClass(g_Width, g_Height, window);
    basecamera = new BaseCameraClass(g_Width, g_Height);
    blendercamera = new BlenderCameraClass(g_Width, g_Height);
    /// 
    blendercamera2 = new BlenderCameraClass2(g_Width, g_Height);
    blendercamera3 = new BlenderCameraClass3(g_Width, g_Height);
    blendercamera4 = new BlenderCameraClass4(g_Width, g_Height);

    blendercamera5 = new BlenderCameraClass5(g_Width, g_Height);
    blendercamera6 = new BlenderCameraClass6(g_Width, g_Height);
    blendercamera7 = new BlenderCameraClass7(g_Width, g_Height);

    quatcamera = new ColoQuatCamera(g_Width, g_Height, window);
    g_ColoQuatCamera = quatcamera;

    TextureSpriteAltasLoader* p_localTextureSpriteAltasLoader = new TextureSpriteAltasLoader();


    cursor_ui_draw = new Cursor_UI_Draw(g_Width, g_Height);
    g_pCursor_UI_Draw = cursor_ui_draw;

    // 
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("7.3.camera8.vs", "7.3.camera8.frag");

    // a cube define
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 cubePositions2[] = {
      glm::vec3(0.0f,  0.0f,  0.0f),
      /*
      glm::vec3(2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f,  2.0f, -2.5f),
      glm::vec3(1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
      */
    };


    // vvtype types::
    // type: 11.0f debug ground dev plane
    // type: 12.0f debug ground dev plane hover
    // type: 13.0f debug ground dev plane selected
    // mainVertices.push_back(11.0f);
    // type: 22.0f graphics cube
    // type: 23.0f graphics cube hover
    // type: 24.0f graphics cube selected
    // mainVertices.push_back(22.0f);
    // type: 33.0f spawned Add Physics Cube
    // type: 34.0f spawned Add Physics Cube in state 1 Collide
    // type: 35.0f spawned Add Physics Cube Selected
    // mainVertices.push_back(33.0f);

    // type: 44.0f spawned Add Triangle for intersection Test
    // type: 45.0f spawned Add Triangle for intersection Test in state 1 Collide
    // type: 46.0f spawned Add Triangle for intersection Test Selected
    // mainVertices.push_back(44.0f);

       // type: 55.0f spawned Add DrawLine_as_Cube for intersection Test
    // type: 56.0f spawned Add DrawLine_as_Cube for intersection Test in state 1 Collide
    // type: 57.0f spawned Add DrawLine_as_Cube for intersection Test Selected
    // mainVertices.push_back(55.0f);



       // type: 66.0f spawned Add Intersection_Cube for intersection Test
    // type: 67.0f spawned Add Intersection_Cube for intersection Test in state 1 Collide
    // type: 68.0f spawned Add Intersection_Cube for intersection Test Selected
    // mainVertices.push_back(66.0f);

      // type: 77.0f spawned Add Cursor_UI_Draw for intersection Test
    // type: 78.0f spawned Add Cursor_UI_Draw for intersection Test in state 1 Collide
    // type: 79.0f spawned Add Cursor_UI_Draw for intersection Test Selected
    // mainVertices.push_back(77.0f);


    //int AddCursorPlane(float x, float y, float z, float width, float height);


  //  glm::vec3 g_triangleVertice1 = glm::vec3(1.5, 1.5, 1.5f);
  //  glm::vec3 g_triangleVertice2 = glm::vec3(1.5, -1.5, 1.5f);
  //  glm::vec3 g_triangleVertice3 = glm::vec3(.75, 0.0f, 1.5f);
    mainVertices.push_back(g_triangleVertice1.x); mainVertices.push_back(g_triangleVertice1.y); mainVertices.push_back(g_triangleVertice1.z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(44.0f);// bottom - left ); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(g_triangleVertice2.x); mainVertices.push_back(g_triangleVertice2.y); mainVertices.push_back(g_triangleVertice2.z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(44.0f);// bottom - right ); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(g_triangleVertice3.x); mainVertices.push_back(g_triangleVertice3.y); mainVertices.push_back(g_triangleVertice3.z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(44.0f);// top -right ); mainVertices.push_back( 2 (top-right)


    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left ); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - right ); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(22.0f);// top -right ); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left ); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(22.0f);// top -right ); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(22.0f);// top - left  ); mainVertices.push_back( 3 (top-left) 



    // face 2
     /*
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom -left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)
    */

    //  mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.051009f); mainVertices.push_back(0.636836f); mainVertices.push_back(22.0f);// bottom -left); mainVertices.push_back( 0 (bottom-left)
   //   mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.051009f); mainVertices.push_back(0.386836f); mainVertices.push_back(22.0f);// bottom - right); mainVertices.push_back( 1 (bottom-right)
    //  mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.301009f); mainVertices.push_back(0.386836f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)


   //   mainVertices.push_back(1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);// top - right); mainVertices.push_back( 2 (top-right)
    //  mainVertices.push_back(1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);// bottom - right); mainVertices.push_back( 1 (bottom-right)

    //  mainVertices.push_back(1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(33.0f);// bottom -left); mainVertices.push_back( 0 (bottom-left)

     //=======================================BARD FIX==============================================//
      // Corrected Face 2, Triangle 1
  // Vertex 0: bottom-left
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); // Position
    mainVertices.push_back(0.051009f); mainVertices.push_back(0.636836f); mainVertices.push_back(22.0f); // Texture/other attributes

    // Vertex 1: bottom-right
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); // Corrected Z value
    mainVertices.push_back(0.051009f); mainVertices.push_back(0.386836f); mainVertices.push_back(22.0f); // Texture/other attributes

    // Vertex 2: top-right
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); // Position
    mainVertices.push_back(0.301009f); mainVertices.push_back(0.386836f); mainVertices.push_back(22.0f); // Texture/other attributes
    //===================================END BARD FIX=================================================//
    // Description:
    // wrongly positioning a triangle in same place as anouther triangle will cause it to be not drawn, making a strange cube rendering effect.
    // there will be whole
    //   |---------------_|
    //   |\               |
    //   |=\              |
    //   |==\             |
    //   |===\            |
    //   |====\           |
    //   |=====\          |
    //   |======\         |
    //   |=======\        |
    //   |========\       |
    //   |=========\      |
    //   |==========\     |
    //   |===========\    |
    //   |============\   |
    //   |=============\  |
    //   |==============\ |
    //   |===============\|
    // the triangle has 2 point in _


    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.051009f); mainVertices.push_back(0.636836f); mainVertices.push_back(22.0f);// bottom -left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.301009f); mainVertices.push_back(0.386836f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.301009f); mainVertices.push_back(0.636836f); mainVertices.push_back(22.0f);// top - left); mainVertices.push_back( 3 (top-left)

    // Triangle 1: 0); mainVertices.push_back( 1); mainVertices.push_back( 2
    // Triangle 2: 0); mainVertices.push_back( 2); mainVertices.push_back( 3
    // face 3
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.390502f); mainVertices.push_back(0.381767f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left) -- 0.390502, 0.381767   .. 0.390502, 0.381767
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.390502f); mainVertices.push_back(0.631767f); mainVertices.push_back(22.0f);// bottom - right); mainVertices.push_back( 1 (bottom-right)  0.390502, 0.631767
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.640502f); mainVertices.push_back(0.381767f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right) -- 2   0.640502, 0.381767 

    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.390502f); mainVertices.push_back(0.381767f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left) 0.390502, 0.381767
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.640502f); mainVertices.push_back(0.381767f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)    0.640502, 0.381767 
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.640502f); mainVertices.push_back(0.631767f); mainVertices.push_back(22.0f);// top - left); mainVertices.push_back( 3 (top-left)      0.640502, 0.631767




    // face 4 
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)

    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - left); mainVertices.push_back( 3 (top-left)



    // Triangle 1: 0); mainVertices.push_back( 1); mainVertices.push_back( 2
    // Triangle 2: 0); mainVertices.push_back( 2); mainVertices.push_back( 3
    // face 5
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - left); mainVertices.push_back( 3 (top-left)




    // face 6

    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)

    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(22.0f);// top - left); mainVertices.push_back( 3 (top-left)

    // add our planes
         // refine as triangles 1
    mainVertices.push_back(5.0f); mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f);//  0 (bottom-left)
    mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f); // 1 (bottom-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f); //  2 (top-right)

    mainVertices.push_back(5.0f); mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f);//  0 (bottom-left)
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f);//  2 (top-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f);//      3 (top-left)    

    // refine as triangles
    mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f); //  0 (bottom-left)
    mainVertices.push_back(5.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f);// 1 (bottom-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f);//  2 (top-right)

    mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f);//  0 (bottom-left)
    mainVertices.push_back(0.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f);//  2 (top-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f); //      3 (top-left)

    // triangle3
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f); //  0 (bottom-left)
    mainVertices.push_back(0.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(11.0f);// 1 (bottom-right)
    mainVertices.push_back(-5.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f); //  2 (top-right)

    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f);  mainVertices.push_back(11.0f);//  0 (bottom-left)
    mainVertices.push_back(-5.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f); //  2 (top-right)
    // refine as triangles
    mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(11.0f);//      3 (top-left)




    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

    //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);

    printf("  mainVertices.size() : %d", mainVertices.size()); //6 attributes 324 , 1 cube 3 planes 





    // 1 cube 6 planes , 12 triangles, 36 vertices
    // 1 plane , 2 triangles 6 vertices
    // 1 cube + 3 planes 36 + 18 = 54 * 6 attributes = 324
   // exit(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // need to see what will be static and predefined and if anything needs alpha blending


    float Mouse_pos_x = 0.0f;
    float Mouse_pos_y = 0.0f;
    float Mouse_pos_z = 0.0f;
    //    float Mouse_width = 64.0f;
    //    float Mouse_height = 64.0f;
    float Mouse_width = 0.64f;
    float Mouse_height = 0.64f;
    int iNumVerts = AddCursorPlane(Mouse_pos_x, Mouse_pos_y, Mouse_pos_z, Mouse_width, Mouse_height);




    // load and create a texture 
    // -------------------------

    unsigned int texture1, texture2, texture3, texture4;

    g_pTextureSpriteAltasLoader->mainPNGGETSprites(); // get file names
    g_pTextureSpriteAltasLoader->mainLoadPNGGETSprites(); // put images into memory
    g_pTextureSpriteAltasLoader->setShader(&ourShader);
    //  g_pTextureSpriteAltasLoader->loadtextureOpenGLContext();

      // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
     // -------------------------------------------------------------------------------------------
    ourShader.use(); // nneeded before the texture init for correctly numbering the textures
    //with setInt
    ourShader.setInt("texture1", 0);
    // 
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    std::string containerPath = "assets/container.jpg";

    unsigned char* data = stbi_load(containerPath.c_str(), &width, &height, &nrChannels, 0);

    //  unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 1" << std::endl;
    }
    stbi_image_free(data);



    ourShader.setInt("texture2", 1);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    std::string awesomefacePath = "assets/awesomeface.png";


    // data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    data = stbi_load(awesomefacePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 2" << std::endl;
    }
    stbi_image_free(data);



    ourShader.setInt("texture3", 2);
    // texture 3
    // ---------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    std::string udpdevcube = "assets/cube_textures_512x512_3.png";


    // data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    data = stbi_load(udpdevcube.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 3" << std::endl;
    }
    stbi_image_free(data);



    ourShader.setInt("texture4", 3);
    // texture 4
  // ---------
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    std::string plane_dev = "assets/plane_dev_512x512.png";


    // data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    data = stbi_load(plane_dev.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 4" << std::endl;
    }
    stbi_image_free(data);

    ourShader.setInt("texture5", 4);
    // texture5 = loadCursorTexture();
    texture5 = cursor_ui_draw->GetCursorTextureID();

    ourShader.setInt("texture6", 5);
    texture6 = g_pTextureSpriteAltasLoader->loadtextureOpenGLContext();

    g_ANA_MainMenuUI->CreateMainMenuQuads();
    g_ANA_GameHUDUI->CreateMainMenuQuads();
    g_pBuildStructure_Cube = new BuildStructure_Cube();
    g_pGoshaRayIntersectionPlaneManager->CreatePlanes(50, 50);


    // ourShader.setInt("texture1", texture1);
   //  ourShader.setInt("texture2", texture2);
   //  ourShader.setInt("texture3", texture3);
   //  ourShader.setInt("texture4", texture4);

    // ourShader.setInt("texture1", 1);
    // ourShader.setInt("texture2", 2);
    // ourShader.setInt("texture3", 3);
    // ourShader.setInt("texture4", 4);
    printf("texture3:%d\n", texture3);
    printf("texture4:%d\n", texture4);;
    printf("texture5:%d\n", texture5);;

    printf("texture6:%d\n", texture6);
    //exit(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
    //    float currentFrame = static_cast<float>(glfwGetTime());
    //    deltaTime = currentFrame - lastFrame;
    //    lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        AddNetworkQue(); // there is better way with lock-free and glMapBuffer way of doing this, adding cubes from the network

        // ui Main Loop
        g_ANA_MainMenuUI->UpdateMainMenu();
        g_ANA_GameHUDUI->UpdateMainMenu();
        // that came from anouther thread.
        // Google:"Sticky Counter"

        if (iTypeCamera == 9)
        {
            quatcamera->update(deltaTime);


        }
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);
        if (texture5 != -1)
        {
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, texture5);

        }


        // activate shader
        ourShader.use();

        updateRealTimeUniforms(ourShader);


        // pass projection matrix to shader (note that in this case it could change every frame)
     //   glm::mat4 projection = glm::perspective(glm::radians(fov), (float)g_Width / (float)g_Height, 0.1f, 100.0f);
      //  glm::mat4 projection = camera2->GetProjectionMatrix();
        glm::mat4 projection = basecamera->GetProjectionMatrix();

        if (iTypeCamera == 2)
        {
            projection = blendercamera->GetProjectionMatrix();

        }
        if (iTypeCamera == 3)
        {
            projection = blendercamera2->GetProjectionMatrix();


        }
        if (iTypeCamera == 4)
        {
            projection = blendercamera3->GetProjectionMatrix();


        }
        if (iTypeCamera == 5)
        {
            projection = blendercamera4->GetProjectionMatrix();
        }
        if (iTypeCamera == 6)
        {
            projection = blendercamera5->GetProjectionMatrix();
        }
        if (iTypeCamera == 7)
        {
            projection = blendercamera6->GetProjectionMatrix();
        }
        if (iTypeCamera == 8)
        {
            projection = blendercamera7->GetProjectionMatrix();
        }
        if (iTypeCamera == 9)
        {
            projection = quatcamera->GetGLMProjectionMatrix();
        }
        // 


        //HeimMat4 projection = heim_mat4_perspective(camera->zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    //    printMat4(projection);

        ourShader.setMat4("projection", projection);

        // camera/view transformation
       // glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
      //  glm::mat4 view = camera2->GetViewMatrix();
        glm::mat4 view = basecamera->GetViewMatrix();

        if (iTypeCamera == 2)
        {
            view = blendercamera->GetViewMatrix();


        }
        if (iTypeCamera == 3)
        {
            view = blendercamera2->GetViewMatrix();


        }
        if (iTypeCamera == 4)
        {
            view = blendercamera3->GetViewMatrix();


        }
        if (iTypeCamera == 5)
        {
            view = blendercamera4->GetViewMatrix();


        }
        if (iTypeCamera == 6)
        {
            view = blendercamera5->GetViewMatrix();
        }
        if (iTypeCamera == 7)
        {
            view = blendercamera6->GetViewMatrix();
        }
        if (iTypeCamera == 8)
        {
            view = blendercamera7->GetViewMatrix();
        }
        if (iTypeCamera == 9)
        {
            view = quatcamera->GetGLMViewMatrix();
        }

        ourShader.setMat4("view", view);

        ourShader.setInt("iUniformsRenderType", iUniformsRenderType);
        renderTime(); // rename update_Render_time() ?
        if (g_EnableClientSidePhysics)
        {
            updateCubes(cubes, deltaTime);
        }
        if (g_syncCubes)
        {
            UpdateDataCubes(cubes, cubeGraphicsData); // need for netcode syncing not just physics
            // need to recode, per cube update, for indexes
            // what if objects spawn, not cubes in between?, maybe allocate alot of invisible cubes.?
        }

        // render boxes
        glBindVertexArray(VAO);
        //  for (unsigned int i = 0; i < 10; i++)
        /*
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
           //  printf("mainVertices.size()/6 :%d", mainVertices.size()/6);
           // exit(0);


            glDrawArrays(GL_TRIANGLES, 0, mainVertices.size() / iNumVertexAttributes);
        }*/

        ////////////////////////////////////////////////////////////////////////////////
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        ourShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, mainVertices.size() / iNumVertexAttributes);
        ////////////////////////////////////////////////////////////////////

        glBindVertexArray(0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{



    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        if (!iFirstConnect)
        {
            // iConnected = mainClient();
          //  iConnected = mainUDPClient();
            iConnected = UDP_Client_Class_Connect();

            iFirstConnect = 1;

        }
    //  glfwSetWindowShouldClose(window, true);

//   int iConnected = 0;
//   int iFirstConnect = 0;


   /*
   float cameraSpeed = static_cast<float>(2.5 * deltaTime);
   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
       cameraPos += cameraSpeed * cameraFront;
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
       cameraPos -= cameraSpeed * cameraFront;
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
       cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
       cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
   */

   //blendercamera.ProcessKeyboardInput();
    camera_movement_t movementtype = NONE;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movementtype = FORWARD;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movementtype = BACKWARD;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movementtype = LEFT;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movementtype = RIGHT;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        movementtype = UP;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        movementtype = DOWN;
    //  camera2->ProcessKeyboard(window, deltaTime);
    if (movementtype != NONE)
    {
        //   basecamera->camera_process_keyboard(movementtype, deltaTime);
        basecamera->ProcessKeyboard(movementtype, deltaTime);
        if (iTypeCamera == 2)
        {
            blendercamera->ProcessKeyboard(movementtype, deltaTime);
        }
        if (iTypeCamera == 3)
        {
            blendercamera2->ProcessKeyboard(movementtype, deltaTime);
        }
        if (iTypeCamera == 4)
        {
            blendercamera3->ProcessKeyboard(movementtype, deltaTime);
        }
        if (iTypeCamera == 5)
        {
            blendercamera4->ProcessKeyboard(movementtype, deltaTime);
        }
        if (iTypeCamera == 6)
        {
            blendercamera5->ProcessKeyboard(movementtype, deltaTime);
        }
        if (iTypeCamera == 7)
        {
            blendercamera6->ProcessKeyboard(movementtype, deltaTime);
        }
        if (iTypeCamera == 8)
        {
            blendercamera7->ProcessKeyboard(movementtype, deltaTime);
        }

    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        iTypeCamera = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        iTypeCamera = 2;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        iTypeCamera = 3;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        iTypeCamera = 4;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        iTypeCamera = 5;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        iTypeCamera = 6;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        iTypeCamera = 7;
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        iTypeCamera = 8;
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        iTypeCamera = 9;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        // Mouse coordinates to test (e.g., the center of the screen)
        int mouse_x = g_Width / 2;   // for firing from ccenter of screen, or testing sanity/testging
        int mouse_y = g_Height / 2;
        std::cout << "Fire Ray" << std::endl;
        // search in glm for this:
    // https://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/raytri/
    // 
    // https://web.archive.org/web/20020201204442/https://www.acm.org/jgt/papers/MollerTrumbore97/
    // https://web.archive.org/web/20020213014728/http://www.acm.org/jgt/papers/MollerTrumbore97/code.html
    // https://web.archive.org/web/20020211055748/http://www.acm.org/jgt/papers/MollerTrumbore97/badouel_code.html
    // 
        // to reverse engineer the intersection code
       // mouse_x = cursor_ui_draw->MouseVirtualX * g_Width;
      //  mouse_y = cursor_ui_draw->MouseVirtualY * g_Height;

        int mouse_x2 = ((cursor_ui_draw->MouseVirtualX + 1.0) * (g_Width / 2));
        int mouse_y2 = g_Height - ((cursor_ui_draw->MouseVirtualY + 1.0) * (g_Height / 2));

        Ray my_ray;



        if (iTypeCamera == 1)
        {


            my_ray = create_ray_from_mouse_normalized(cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY, g_Width, g_Height, basecamera->GetViewMatrix(), basecamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 2)
        {

            //  printf("mouse_x2 %d, mouse_y2: %d\n", mouse_x2, mouse_y2);

          //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera->GetViewMatrix(), blendercamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 3)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
          //  my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

            my_ray = create_ray_from_mouse_unproject(mouse_x, mouse_y, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

        }
        if (iTypeCamera == 4)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera3->GetViewMatrix(), blendercamera3->GetProjectionMatrix());
        }

        if (iTypeCamera == 5)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera4->GetViewMatrix(), blendercamera4->GetProjectionMatrix());
        }
        if (iTypeCamera == 6)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera5->GetViewMatrix(), blendercamera5->GetProjectionMatrix());
        }
        if (iTypeCamera == 7)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera6->GetViewMatrix(), blendercamera6->GetProjectionMatrix());
        }
        if (iTypeCamera == 8)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera7->GetViewMatrix(), blendercamera7->GetProjectionMatrix());
        }

        if (iTypeCamera == 9)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            quatcamera->updateCameraMatrixes();
            printf("my_ray = quatcamera\n");
            my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, quatcamera->GetGLMViewMatrix(), quatcamera->GetGLMProjectionMatrix());
        }

        glm::vec4 rayColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

        glm::vec3 startPos = my_ray.origin;

        //   glm::vec3 endPos = my_ray.origin + my_ray.direction;
        glm::vec3 direction = my_ray.direction;

        float width = 0.01f;
        // int iNumberVertexesAdded = AddCubeLine(startPos,  endPos,  width, rayColor);

        int iNumberVertexesAdded = AddCubeLine2(startPos, direction, width, rayColor);


        //  checkMouseClick(create_ray_from_mouse
        glm::vec3 triangleVertice1 = glm::vec3(1.5, 1.5, 1.5f);
        glm::vec3 triangleVertice2 = glm::vec3(1.5, -1.5, 1.5f);
        glm::vec3 triangleVertice3 = glm::vec3(.75, 0.0f, 1.5f);

        bool Didhit = false;
        float t2 = 0.0f;

        glm::vec2 vec2return = checkMouseClick2(my_ray, triangleVertice1, triangleVertice2, triangleVertice3, Didhit, t2);

        std::cout << "Ray Origin: (" << my_ray.origin.x << ", " << my_ray.origin.y << ", " << my_ray.origin.z << ")" << std::endl;
        std::cout << "Ray Direction: (" << my_ray.direction.x << ", " << my_ray.direction.y << ", " << my_ray.direction.z << ")" << std::endl;

        std::cout << "vec2return.g: (" << vec2return.g << std::endl;
        std::cout << "vec2return.length: (" << vec2return.length << std::endl;

        if (Didhit) {
            // Calculate the world space intersection point using the ray's parametric equation:
            // P = Origin + Direction * t
            glm::vec3 intersection_point = my_ray.origin + my_ray.direction * t2;

            std::cout << "Ray HIT the triangle!" << std::endl;
            std::cout << "Intersection Point: ("
                << intersection_point.x << ", "
                << intersection_point.y << ", "
                << intersection_point.z << ")" << std::endl;

            float cubeWidth = 0.25;


            int iNumVertsAlloc = AddIntersectionCube2(intersection_point.x, intersection_point.y, intersection_point.z, cubeWidth);
            int iNumberVertexesAdded2 = AddCubeLine3(startPos, direction, width, rayColor, t2);

        }
        else {
            std::cout << "Ray DID NOT HIT the triangle. 1" << std::endl;
        }


    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {

        AddCube(1.5f, -1.5f, 1.5f);

        printf(" AddCube(1.5f, -1.5f, 1.5f);");


    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        // float random_float = (float)rand() / (float)RAND_MAX;
        int random_number = 10 + rand() % (25 - 10 + 1);


        AddCube(
            (float)rand() * static_cast<float>(random_number) / (float)RAND_MAX,
            (float)rand() * static_cast<float>(random_number) / (float)RAND_MAX,
            (float)rand() * static_cast<float>(random_number) / (float)RAND_MAX
        );

        printf(" AddCube(1.5f, -1.5f, 1.5f);");


    }
    // iUniformsRenderType
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        iUniformsRenderType = 1;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        iUniformsRenderType = 2;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        iUniformsRenderType = 3;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        iUniformsRenderType = 4;

    // TIP switch math to use blender coordinate system, will be easier to tranfer over assets and scenes
    // yaw
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        yaw += 1;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        yaw -= 1;


    // pitch
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        pitch += 1;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        pitch -= 1;


    // x
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        cameraPos.x += 1;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        cameraPos.x -= 1;

    // y
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        cameraPos.y += 1;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        cameraPos.y -= 1;

    // z
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos.z += 1;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos.z -= 1;


    // g_pBuildStructure_Cube
    if (glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS)
    {
        printf("\ng_pBuildStructure_Cube: index: %d\n", g_pBuildStructure_Cube->CastCubeIndex);
        printf("x: %f, y: %f, z: %f\n", mainVertices[g_pBuildStructure_Cube->CastCubeIndex], mainVertices[g_pBuildStructure_Cube->CastCubeIndex + 1], mainVertices[g_pBuildStructure_Cube->CastCubeIndex + 2]);
        printf("u: %f, v: %f, vvtype: %f\n", mainVertices[g_pBuildStructure_Cube->CastCubeIndex + 3], mainVertices[g_pBuildStructure_Cube->CastCubeIndex + 4], mainVertices[g_pBuildStructure_Cube->CastCubeIndex + 5]);

    }
    if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
    {
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float fdata[256];
        // Example: Getting the data for the element at index 5 (the 6th element, 0-indexed)
        unsigned int desiredIndex = g_pBuildStructure_Cube->CastCubeIndex;
        size_t elementSize = 6 * sizeof(float);
        size_t offset = desiredIndex * elementSize;

        glGetBufferSubData(
            GL_ARRAY_BUFFER, // target (must be the one currently bound)
            (GLintptr)g_pBuildStructure_Cube->CastCubeIndex * sizeof(float),  // offset into the buffer in bytes
            (GLsizeiptr)elementSize, // size of the data to retrieve in bytes
            fdata             // pointer to CPU memory to write to
        );
        ////  Print the Values :
        //  The data array now holds the 6 float values from the VBO at the specified index, which you can print out.

          //    C
        printf("\ng_pBuildStructure_Cube: index: %d\n", g_pBuildStructure_Cube->CastCubeIndex);
        for (int i = 0; i < 6; ++i) {
            printf("Value %d: %f\n", i, fdata[i]);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
    if (iTypeCamera == 9)
    {
        //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
     //   my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, quatcamera->GetGLMViewMatrix(), quatcamera->GetGLMProjectionMatrix());
     //   quatcamera->lookAt2DRect2(cameraPos.x, cameraPos.y, g_Width, g_Height);
      //  quatcamera->lookAt2DRect(cameraPos.x, cameraPos.y, g_Width, g_Height);

    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
    {
        g_EnableClientSidePhysics = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
    {
        g_EnableClientSidePhysics = 0;
    }
    //  printf("yaw: %f, pitch: %f, camera.x: %f, camera.y: %f, camera.z: %f \n ", yaw, pitch, cameraPos.x, cameraPos.y, cameraPos.z);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    //blendercamera->ProcessMouseMovement(xposIn, yposIn);
  //  camera2->ProcessMouseMovement(xposIn, yposIn);
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    cursor_ui_draw->mouse_callback(window, xpos, ypos);

    g_pBuildStructure_Cube->mouse_callback(window, xpos, ypos);

    //  camera2->camera_process_mouse_movement(xpos, ypos, true);
    basecamera->ProcessMouseMovement(xpos, ypos, true);
    if (iTypeCamera == 2)
    {
        blendercamera->ProcessMouseMovement(xpos, ypos, true);
        //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
     //   my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera->GetViewMatrix(), blendercamera->GetProjectionMatrix());
    }
    if (iTypeCamera == 3)
    {
        blendercamera2->ProcessMouseMovement(xpos, ypos, true);
        //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
     //   my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera->GetViewMatrix(), blendercamera->GetProjectionMatrix());
    }
    if (iTypeCamera == 4)
    {
        blendercamera3->ProcessMouseMovement(xpos, ypos, true);
        //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
     //   my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera->GetViewMatrix(), blendercamera->GetProjectionMatrix());
    }
    if (iTypeCamera == 5)
    {
        blendercamera4->ProcessMouseMovement(xpos, ypos, true);
    }
    if (iTypeCamera == 6)
    {
        blendercamera5->ProcessMouseMovement(xpos, ypos, true);
    }
    if (iTypeCamera == 7)
    {
        blendercamera6->ProcessMouseMovement(xpos, ypos, true);
    }
    if (iTypeCamera == 8)
    {
        blendercamera7->ProcessMouseMovement(xpos, ypos, true);
    }

    if (iTypeCamera == 9)
    {
        //  quatcamera->ProcessMouseMovement(xpos, ypos, true);

        quatcamera->mouseCallback(window, xposIn, yposIn);
        quatcamera->updateCameraMatrixes();
    }

    //  UpdateMousePos(xpos, ypos);


      /*
      float xpos = static_cast<float>(xposIn);
      float ypos = static_cast<float>(yposIn);

      if (firstMouse)
      {
          lastX = xpos;
          lastY = ypos;
          firstMouse = false;
      }

      float xoffset = xpos - lastX;
      float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
      lastX = xpos;
      lastY = ypos;

      float sensitivity = 0.1f; // change this value to your liking
      xoffset *= sensitivity;
      yoffset *= sensitivity;

      yaw += xoffset;
      pitch += yoffset;

      // make sure that when pitch is out of bounds, screen doesn't get flipped
      if (pitch > 89.0f)
          pitch = 89.0f;
      if (pitch < -89.0f)
          pitch = -89.0f;

      glm::vec3 front;
      front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
      front.y = sin(glm::radians(pitch));
      front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
      cameraFront = glm::normalize(front);
      */
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // camera2->camera_process_mouse_scroll(yoffset);
    float fyoffset = static_cast<float>(yoffset);

    basecamera->ProcessMouseScroll(fyoffset);
    if (iTypeCamera == 2)
    {// blendercamera
        blendercamera->ProcessMouseScroll(fyoffset);
    }
    if (iTypeCamera == 3)
    {// blendercamera
        blendercamera2->ProcessMouseScroll(fyoffset);
    }
    if (iTypeCamera == 4)
    {// blendercamera
        blendercamera3->ProcessMouseScroll(fyoffset);
    }
    if (iTypeCamera == 5)
    {// blendercamera
        blendercamera4->ProcessMouseScroll(fyoffset);
    }
    if (iTypeCamera == 6)
    {// blendercamera
        blendercamera5->ProcessMouseScroll(fyoffset);
    }
    if (iTypeCamera == 7)
    {// blendercamera
        blendercamera6->ProcessMouseScroll(fyoffset);
    }
    if (iTypeCamera == 8)
    {// blendercamera
        blendercamera7->ProcessMouseScroll(fyoffset);
    }

    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    // if (fov > 45.0f)
   //      fov = 45.0f;
   //      if (fov > 450.0f)
   //      fov = 450.0f;
    if (fov > 100.0f)
        fov = 100.0f;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    g_mouse_button = button;
    g_mouse_action = action;
    g_mouse_mods = mods;

    g_ANA_MainMenuUI->mouse_button_callback(window, button, action, mods);

    g_pBuildStructure_Cube->mouse_button_callback(window, button, action, mods);

    //auto camera = static_cast<BlenderCameraClass5*>(glfwGetWindowUserPointer(window));//C++ garbage
    BlenderCameraClass5* camera = blendercamera5;

    if (camera) {
        if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            if (action == GLFW_PRESS) {
                camera->is_middle_button_pressed = true;
                camera->is_shift_pressed = (mods & GLFW_MOD_SHIFT);
            }
            else if (action == GLFW_RELEASE) {
                camera->is_middle_button_pressed = false;
            }
        }
    }




    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //   double xpos, ypos;
           // Get the cursor position in screen coordinates
         //  glfwGetCursorPos(window, &xpos, &ypos);

           // 1. Normalize device coordinates (NDC) from screen coordinates
         //  float x = (2.0f * xpos) / g_Width - 1.0f;
         //  float y = 1.0f - (2.0f * ypos) / g_Height;

        int mouse_x2 = ((cursor_ui_draw->MouseVirtualX + 1.0) * (g_Width / 2));
        int mouse_y2 = g_Height - ((cursor_ui_draw->MouseVirtualY + 1.0) * (g_Height / 2));
        float x = ((cursor_ui_draw->MouseVirtualX + 1.0) * (g_Width / 2));
        float y = g_Height - ((cursor_ui_draw->MouseVirtualY + 1.0) * (g_Height / 2));

        printf("cursor_ui_draw->MouseVirtualX %f, cursor_ui_draw->MouseVirtualY: %f\n", cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY);
        printf("x mouse_x2 %f, y mouse_y2: %f\n", x, y);


        float z = 1.0f;
        glm::vec3 ray_nds = glm::vec3(x, y, z);

        // 2. Homogeneous Clip Space
        glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

        // 3. Eye Space
       // glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 projectionMatrix = basecamera->GetProjectionMatrix();
        if (iTypeCamera == 2)
        {// blendercamera
            projectionMatrix = blendercamera->GetProjectionMatrix();
        }
        if (iTypeCamera == 3)
        {// blendercamera
            projectionMatrix = blendercamera2->GetProjectionMatrix();
        }
        if (iTypeCamera == 4)
        {// blendercamera
            projectionMatrix = blendercamera3->GetProjectionMatrix();
        }
        if (iTypeCamera == 5)
        {// blendercamera
            projectionMatrix = blendercamera4->GetProjectionMatrix();
        }
        if (iTypeCamera == 6)
        {// blendercamera
            projectionMatrix = blendercamera5->GetProjectionMatrix();
        }
        if (iTypeCamera == 7)
        {// blendercamera
            projectionMatrix = blendercamera6->GetProjectionMatrix();
        }
        if (iTypeCamera == 8)
        {// blendercamera
            projectionMatrix = blendercamera7->GetProjectionMatrix();
        }
        if (iTypeCamera == 9)
        {// blendercamera
            projectionMatrix = quatcamera->GetGLMProjectionMatrix();
        }

        glm::mat4 inverseProjection = glm::inverse(projectionMatrix);
        glm::vec4 ray_eye = inverseProjection * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f); // fires the ray to the right

        // 4. World Space
    //    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 viewMatrix = basecamera->GetViewMatrix();
        if (iTypeCamera == 2)
        {// blendercamera
            viewMatrix = blendercamera->GetViewMatrix();
        }
        if (iTypeCamera == 3)
        {// blendercamera
            viewMatrix = blendercamera2->GetViewMatrix();
        }
        if (iTypeCamera == 4)
        {// blendercamera
            viewMatrix = blendercamera3->GetViewMatrix();
        }
        if (iTypeCamera == 5)
        {// blendercamera
            viewMatrix = blendercamera4->GetViewMatrix();
        }
        if (iTypeCamera == 6)
        {// blendercamera
            viewMatrix = blendercamera5->GetViewMatrix();
        }
        if (iTypeCamera == 7)
        {// blendercamera
            viewMatrix = blendercamera6->GetViewMatrix();
        }
        if (iTypeCamera == 8)
        {// blendercamera
            viewMatrix = blendercamera7->GetViewMatrix();
        }

        if (iTypeCamera == 9)
        {// blendercamera
            viewMatrix = quatcamera->GetGLMViewMatrix();
        }

        glm::mat4 inverseView = glm::inverse(viewMatrix);
        glm::vec4 ray_world = inverseView * ray_eye;
        glm::vec3 ray_dir = glm::normalize(glm::vec3(ray_world)); //  glm::vec3 direction = my_ray.direction;

        // Now you have the ray origin and direction in world space
         //glm::vec3 ray_origin = cameraPos; // can be used with camera 2 radar for ray cast somewhere elese
        Ray my_ray;

        if (iTypeCamera == 1)
        {


            my_ray = create_ray_from_mouse_normalized(cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY, g_Width, g_Height, basecamera->GetViewMatrix(), basecamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 2)
        {

            //  printf("mouse_x2 %d, mouse_y2: %d\n", mouse_x2, mouse_y2);

          //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera->GetViewMatrix(), blendercamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 3)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
          //  my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

            my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

        }
        if (iTypeCamera == 4)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera3->GetViewMatrix(), blendercamera3->GetProjectionMatrix());
        }

        if (iTypeCamera == 5)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera4->GetViewMatrix(), blendercamera4->GetProjectionMatrix());
        }
        if (iTypeCamera == 6)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera5->GetViewMatrix(), blendercamera5->GetProjectionMatrix());
        }
        if (iTypeCamera == 7)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera6->GetViewMatrix(), blendercamera6->GetProjectionMatrix());
        }
        if (iTypeCamera == 8)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera7->GetViewMatrix(), blendercamera7->GetProjectionMatrix());
        }

        if (iTypeCamera == 9)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            quatcamera->updateCameraMatrixes();
            printf("my_ray = quatcamera\n");
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, quatcamera->GetGLMViewMatrix(), quatcamera->GetGLMProjectionMatrix());
        }
        glm::vec3 ray_origin = my_ray.origin;
        ray_dir = my_ray.direction;

        glm::vec3 ray_destination = my_ray.origin + glm::normalize(my_ray.direction) * 10.0f; // temp for cube update place


        // https://www.youtube.com/watch?v=T1tXepGXDDM
        // 
    //    std::cout << "Mouse clicked at screen coordinates: (" << xpos << ", " << ypos << ")" << std::endl;
        // cursor_ui_draw->MouseVirtualX
        std::cout << "Mouse clicked at screen coordinates: (" << cursor_ui_draw->MouseVirtualX << ", " << cursor_ui_draw->MouseVirtualY << ")" << std::endl;

        std::cout << "Normalized Device Coordinates: (" << x << ", " << y << ")" << std::endl;
        std::cout << "Ray Origin (World Space): (" << ray_origin.x << ", " << ray_origin.y << ", " << ray_origin.z << ")" << std::endl;
        std::cout << "Ray Direction (World Space): (" << ray_dir.x << ", " << ray_dir.y << ", " << ray_dir.z << ")" << std::endl;

        int client_id_udp = GetClientID(); // move this to a GameCoordinator Class, and a API AllainceAndAllegenceID class
        int selected_cube_id_udp = 1; // fix the raytrace detection, by adding to more objects

        int client_id = client_id_udp; // GetClientID, flag_COMMAND_REFRESH_UDP_ID
        int object_id = selected_cube_id_udp; // selected_cube_client_id, selected_cube_server_id
        std::cout << "Error: Get clientid from server:" << std::endl;
        std::cout << "Error: Get objectid from server/client?:" << std::endl;

        MoveCommand cmd;
        cmd.player_id = client_id;
        cmd.object_id = object_id;
        cmd.destination = { x, y, z };

        MessageHeader header;
        header.type = MOVE_COMMAND;
        header.size = sizeof(MoveCommand);

        send_message_udp_queue(header, (const char*)&cmd);

        // From here, you would perform ray-AABB or ray-triangle intersection tests
        // to see which object the ray hits.
        // For example, to check if it hits the cube at origin:
        // (This is a simplified example, a proper intersection test is more complex)
      //  glm::vec3 boxMin = glm::vec3(-0.5f, -0.5f, -0.5f);
     //   glm::vec3 boxMax = glm::vec3(0.5f, 0.5f, 0.5f);
        float width2 = 0.02f;
        glm::vec4 rayColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        int iNumberVertexesAdded2 = AddCubeLine2(ray_origin, ray_dir, width2, rayColor);


        glm::vec3 boxMin = glm::vec3(-2.0f, -2.0f, 1.0f);
        glm::vec3 boxMax = glm::vec3(-1.0f, -1.0f, 2.0f);

        // A simple ray-box intersection check (slab method)
        float t1 = (boxMin.x - ray_origin.x) / ray_dir.x;
        float t2 = (boxMax.x - ray_origin.x) / ray_dir.x;
#if defined(_WIN32) || defined(_WIN64)
        float tmin = min(t1, t2);
        float tmax = max(t1, t2);
#else
        float tmin = glm::min(t1, t2);
        float tmax = glm::max(t1, t2);
#endif
        t1 = (boxMin.y - ray_origin.y) / ray_dir.y;
        t2 = (boxMax.y - ray_origin.y) / ray_dir.y;
        //   tmin = glm::max(tmin, glm::min(t1, t2));
        //   tmax = glm::min(tmax, glm::max(t1, t2));
#if defined(_WIN32) || defined(_WIN64)
        tmin = min(t1, t2);
        tmax = max(t1, t2);
#else
        tmin = glm::min(t1, t2);
        tmax = glm::max(t1, t2);
#endif

        t1 = (boxMin.z - ray_origin.z) / ray_dir.z;
        t2 = (boxMax.z - ray_origin.z) / ray_dir.z;
        //      tmin = glm::max(tmin, glm::min(t1, t2));
         //     tmax = glm::min(tmax, glm::max(t1, t2));
#if defined(_WIN32) || defined(_WIN64)
        tmin = min(t1, t2);
        tmax = max(t1, t2);
#else
        tmin = glm::min(t1, t2);
        tmax = glm::max(t1, t2);
#endif


        // if (tmax > glm::max(0.0f, tmin)) {
#if defined(_WIN32) || defined(_WIN64)
        if (tmax > max(0.0f, tmin)) {
#else
        if (tmax > glm::max(0.0f, tmin)) {
#endif
            std::cout << "The ray intersects with the cube!" << std::endl;
            if (g_pBuildStructure_Cube)
            {
                g_pBuildStructure_Cube->UpdateCastLocationCube(ray_destination.x, ray_destination.y, ray_destination.z, 3.0f);
            }
        }
        else {
            std::cout << "The ray does not intersect with the cube." << std::endl;
        }
        }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

        // ray cast
        std::cout << "Fire Ray GLFW_MOUSE_BUTTON_RIGHT" << std::endl;
        // search in glm for this:
    // https://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/raytri/
        // to reverse engineer the intersection code
       // mouse_x = cursor_ui_draw->MouseVirtualX * g_Width;
      //  mouse_y = cursor_ui_draw->MouseVirtualY * g_Height;

        int mouse_x2 = ((cursor_ui_draw->MouseVirtualX + 1.0) * (g_Width / 2));
        int mouse_y2 = g_Height - ((cursor_ui_draw->MouseVirtualY + 1.0) * (g_Height / 2));


        printf("cursor_ui_draw->MouseVirtualX %f, cursor_ui_draw->MouseVirtualY: %f\n", cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY);
        printf("mouse_x2 %d, mouse_y2: %d\n", mouse_x2, mouse_y2);
        Ray my_ray;

        if (iTypeCamera == 1)
        {


            my_ray = create_ray_from_mouse_normalized(cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY, g_Width, g_Height, basecamera->GetViewMatrix(), basecamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 2)
        {

            //  printf("mouse_x2 %d, mouse_y2: %d\n", mouse_x2, mouse_y2);

          //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera->GetViewMatrix(), blendercamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 3)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
          //  my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

            my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

        }
        if (iTypeCamera == 4)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera3->GetViewMatrix(), blendercamera3->GetProjectionMatrix());
        }

        if (iTypeCamera == 5)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera4->GetViewMatrix(), blendercamera4->GetProjectionMatrix());
        }
        if (iTypeCamera == 6)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera5->GetViewMatrix(), blendercamera5->GetProjectionMatrix());
        }
        if (iTypeCamera == 7)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera6->GetViewMatrix(), blendercamera6->GetProjectionMatrix());
        }
        if (iTypeCamera == 8)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera7->GetViewMatrix(), blendercamera7->GetProjectionMatrix());
        }

        if (iTypeCamera == 9)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            quatcamera->updateCameraMatrixes();
            printf("my_ray = quatcamera\n");
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, quatcamera->GetGLMViewMatrix(), quatcamera->GetGLMProjectionMatrix());
        }

        glm::vec4 rayColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

        glm::vec3 startPos = my_ray.origin;

        //   glm::vec3 endPos = my_ray.origin + my_ray.direction;
        glm::vec3 direction = my_ray.direction;

        float width = 0.01f;
        // int iNumberVertexesAdded = AddCubeLine(startPos,  endPos,  width, rayColor);

        int iNumberVertexesAdded = AddCubeLine2(startPos, direction, width, rayColor);


        //  checkMouseClick(create_ray_from_mouse
     //   glm::vec3 triangleVertice1 = glm::vec3(1.5, 1.5, 1.5f);
     //   glm::vec3 triangleVertice2 = glm::vec3(1.5, -1.5, 1.5f);
      //  glm::vec3 triangleVertice3 = glm::vec3(.75, 0.0f, 1.5f);

        bool Didhit = false;
        float t2 = 0.0f;

        for (int iCubeIndex = 0; iCubeIndex < cubes.size(); iCubeIndex++)
        {
            int iCubeVerticeIndex = cubeGraphicsData[iCubeIndex].mainVerticesIndex;


            glm::vec3 triangleVertice1 = glm::vec3(mainVertices[iCubeVerticeIndex], mainVertices[iCubeVerticeIndex + 1], mainVertices[iCubeVerticeIndex + 2]);
            glm::vec3 triangleVertice2 = glm::vec3(mainVertices[iCubeVerticeIndex + 6], mainVertices[iCubeVerticeIndex + 7], mainVertices[iCubeVerticeIndex + 8]);
            glm::vec3 triangleVertice3 = glm::vec3(mainVertices[iCubeVerticeIndex + 12], mainVertices[iCubeVerticeIndex + 13], mainVertices[iCubeVerticeIndex + 14]);


            //AddTriangleTest(triangleVertice1, triangleVertice2, triangleVertice3);//add a duplicate model where ray hit


            glm::vec2 vec2return = checkMouseClick2(my_ray, triangleVertice1, triangleVertice2, triangleVertice3, Didhit, t2);

            std::cout << "Ray Origin: (" << my_ray.origin.x << ", " << my_ray.origin.y << ", " << my_ray.origin.z << ")" << std::endl;
            std::cout << "Ray Direction: (" << my_ray.direction.x << ", " << my_ray.direction.y << ", " << my_ray.direction.z << ")" << std::endl;

            std::cout << "vec2return.g: (" << vec2return.g << std::endl;
            std::cout << "vec2return.length: (" << vec2return.length << std::endl;

            if (Didhit) {
                // Calculate the world space intersection point using the ray's parametric equation:
                // P = Origin + Direction * t
                glm::vec3 intersection_point = my_ray.origin + my_ray.direction * t2;

                std::cout << "Ray HIT the triangle!" << std::endl;
                std::cout << "Intersection Point: ("
                    << intersection_point.x << ", "
                    << intersection_point.y << ", "
                    << intersection_point.z << ")" << std::endl;

                float cubeWidth = 0.25;


                int iNumVertsAlloc = AddIntersectionCube2(intersection_point.x, intersection_point.y, intersection_point.z, cubeWidth);
                int iNumberVertexesAdded2 = AddCubeLine3(startPos, direction, width, rayColor, t2);

                std::cout << "Hit Cube Index: ("
                    << iCubeIndex
                    << ");"
                    << std::endl;

                mainVertices[iCubeVerticeIndex + 5] = 34.0f;
                mainVertices[iCubeVerticeIndex + 11] = 34.0f;
                mainVertices[iCubeVerticeIndex + 17] = 34.0f;

                //    NetworkVector3 impulseAdd;
                 //   impulseAdd.x = direction.x;
                 //   impulseAdd.y = direction.y;
                 //   impulseAdd.z = direction.z;
                 //   float yPower = 10.0f;

                float xPower = 1.0f;
                float yPower = 1.0f;
                float zPower = 10.0f;
                cubes[iCubeIndex].velocity.x += direction.x * xPower;
                cubes[iCubeIndex].velocity.y += direction.y * yPower;
                cubes[iCubeIndex].velocity.z += direction.z * zPower;

            }
            else {
                std::cout << "Ray DID NOT HIT the triangle. 2" << std::endl;
            }

        }

    }


    if (button == GLFW_MOUSE_BUTTON_4 && action == GLFW_PRESS) {

        // ray cast
        std::cout << "Fire Ray GLFW_MOUSE_BUTTON_RIGHT" << std::endl;
        // search in glm for this:
    // https://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/raytri/
        // to reverse engineer the intersection code
       // mouse_x = cursor_ui_draw->MouseVirtualX * g_Width;
      //  mouse_y = cursor_ui_draw->MouseVirtualY * g_Height;

        int mouse_x2 = ((cursor_ui_draw->MouseVirtualX + 1.0) * (g_Width / 2));
        int mouse_y2 = g_Height - ((cursor_ui_draw->MouseVirtualY + 1.0) * (g_Height / 2));

        Ray my_ray;



        if (iTypeCamera == 1)
        {


            my_ray = create_ray_from_mouse_normalized(cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY, g_Width, g_Height, basecamera->GetViewMatrix(), basecamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 2)
        {

            //  printf("mouse_x2 %d, mouse_y2: %d\n", mouse_x2, mouse_y2);

          //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera->GetViewMatrix(), blendercamera->GetProjectionMatrix());
        }
        if (iTypeCamera == 3)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
          //  my_ray = create_ray_from_mouse(mouse_x, mouse_y, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

            my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera2->GetViewMatrix(), blendercamera2->GetProjectionMatrix());

        }
        if (iTypeCamera == 4)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera3->GetViewMatrix(), blendercamera3->GetProjectionMatrix());
        }

        if (iTypeCamera == 5)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera4->GetViewMatrix(), blendercamera4->GetProjectionMatrix());
        }
        if (iTypeCamera == 6)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera5->GetViewMatrix(), blendercamera5->GetProjectionMatrix());
        }
        if (iTypeCamera == 7)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera6->GetViewMatrix(), blendercamera6->GetProjectionMatrix());
        }
        if (iTypeCamera == 8)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera7->GetViewMatrix(), blendercamera7->GetProjectionMatrix());
        }

        if (iTypeCamera == 9)
        {
            //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
            quatcamera->updateCameraMatrixes();
            printf("my_ray = quatcamera\n");
            my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, quatcamera->GetGLMViewMatrix(), quatcamera->GetGLMProjectionMatrix());
        }

        glm::vec4 rayColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

        glm::vec3 startPos = my_ray.origin;

        //   glm::vec3 endPos = my_ray.origin + my_ray.direction;
        glm::vec3 direction = my_ray.direction;

        float width = 0.01f;
        // int iNumberVertexesAdded = AddCubeLine(startPos,  endPos,  width, rayColor);

        int iNumberVertexesAdded = AddCubeLine2(startPos, direction, width, rayColor);


        //  checkMouseClick(create_ray_from_mouse
     //   glm::vec3 triangleVertice1 = glm::vec3(1.5, 1.5, 1.5f);
     //   glm::vec3 triangleVertice2 = glm::vec3(1.5, -1.5, 1.5f);
      //  glm::vec3 triangleVertice3 = glm::vec3(.75, 0.0f, 1.5f);

        bool Didhit = false;
        float t2 = 0.0f;

        for (int iCubeIndex = 0; iCubeIndex < cubes.size(); iCubeIndex++)
        {
            int iCubeVerticeIndex = cubeGraphicsData[iCubeIndex].mainVerticesIndex;
            Didhit = false;
            t2 = 0.0f;

            int iNumMeshTriangles = 12;
            for (int iNumMeshTrianglesIndex = 0; iNumMeshTrianglesIndex < iNumMeshTriangles; iNumMeshTrianglesIndex++)
            {
                //   Didhit = false;
                //    t2 = 0.0f;
                int iAddIndex = iNumMeshTrianglesIndex * 18;

                glm::vec3 triangleVertice1 = glm::vec3(mainVertices[iAddIndex + iCubeVerticeIndex], mainVertices[iAddIndex + iCubeVerticeIndex + 1], mainVertices[iAddIndex + iCubeVerticeIndex + 2]);
                glm::vec3 triangleVertice2 = glm::vec3(mainVertices[iAddIndex + iCubeVerticeIndex + 6], mainVertices[iAddIndex + iCubeVerticeIndex + 7], mainVertices[iAddIndex + iCubeVerticeIndex + 8]);
                glm::vec3 triangleVertice3 = glm::vec3(mainVertices[iAddIndex + iCubeVerticeIndex + 12], mainVertices[iAddIndex + iCubeVerticeIndex + 13], mainVertices[iAddIndex + iCubeVerticeIndex + 14]);


                //AddTriangleTest(triangleVertice1, triangleVertice2, triangleVertice3);//add a duplicate model where ray hit


                glm::vec2 vec2return = checkMouseClick2(my_ray, triangleVertice1, triangleVertice2, triangleVertice3, Didhit, t2);

                std::cout << "Ray Origin: (" << my_ray.origin.x << ", " << my_ray.origin.y << ", " << my_ray.origin.z << ")" << std::endl;
                std::cout << "Ray Direction: (" << my_ray.direction.x << ", " << my_ray.direction.y << ", " << my_ray.direction.z << ")" << std::endl;

                std::cout << "vec2return.g: (" << vec2return.g << std::endl;
                std::cout << "vec2return.length: (" << vec2return.length << std::endl;
                if (Didhit) {
                    std::cout << "Hit Cube Index: ("
                        << iCubeIndex
                        << std::endl
                        << "iAddIndex: "
                        << iAddIndex
                        << ");"
                        << std::endl;

                    mainVertices[iAddIndex + iCubeVerticeIndex + 5] = 34.0f;
                    mainVertices[iAddIndex + iCubeVerticeIndex + 11] = 34.0f;
                    mainVertices[iAddIndex + iCubeVerticeIndex + 17] = 34.0f;
                }

            }

            if (Didhit) {
                // Calculate the world space intersection point using the ray's parametric equation:
                // P = Origin + Direction * t
                glm::vec3 intersection_point = my_ray.origin + my_ray.direction * t2;

                std::cout << "Ray HIT the triangle!" << std::endl;
                std::cout << "Intersection Point: ("
                    << intersection_point.x << ", "
                    << intersection_point.y << ", "
                    << intersection_point.z << ")" << std::endl;

                float cubeWidth = 0.25;


                int iNumVertsAlloc = AddIntersectionCube2(intersection_point.x, intersection_point.y, intersection_point.z, cubeWidth);
                int iNumberVertexesAdded2 = AddCubeLine3(startPos, direction, width, rayColor, t2);

                //  iAddIndex +


                //    NetworkVector3 impulseAdd;
                 //   impulseAdd.x = direction.x;
                 //   impulseAdd.y = direction.y;
                 //   impulseAdd.z = direction.z;
                 //   float yPower = 10.0f;

                float xPower = 1.0f;
                float yPower = 1.0f;
                float zPower = 10.0f;
                cubes[iCubeIndex].velocity.x += direction.x * xPower;
                cubes[iCubeIndex].velocity.y += direction.y * yPower;
                cubes[iCubeIndex].velocity.z += direction.z * zPower;
                Didhit = false;
                t2 = 0.0f;
            }
            else {
                std::cout << "Ray DID NOT HIT the triangle. 3" << std::endl;
            }

        }

    }


    }
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    //   auto camera = static_cast<BlenderCameraClass5*>(glfwGetWindowUserPointer(window));
    BlenderCameraClass5* camera = blendercamera5;
    if (camera) {
        if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) {
            if (action == GLFW_PRESS) {
                camera->is_shift_pressed = true;
            }
            else if (action == GLFW_RELEASE) {
                camera->is_shift_pressed = false;
            }
        }
    }


    if (iTypeCamera == 9)
    {
        //  quatcamera->ProcessKeyboard(movementtype, deltaTime);
       // quatcamera->keyCallbackDebug(window, key, scancode, action, mods);
        quatcamera->keyCallback(window, key, scancode, action, mods);

    }
}
