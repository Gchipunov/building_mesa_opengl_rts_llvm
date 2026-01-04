#include <vector>
#include <glm/glm.hpp>

//#include <glad/glad.h>
#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
#include <GLFW/glfw3.h>

//#include "UDPClient_update-AABB-Cubes.h"
#include "UDPClient_update_data_Cubes.h"

//extern std::vector <CubeGraphicsData> cubeGraphicsData;

std::vector <CubeGraphicsData> cubeGraphicsData;

extern std::vector<float> mainVertices;
extern GLuint VAO;
extern GLuint VBO;
extern int iNumVertexAttributes; // 6

#define NUM_CUBE_SIDES 6
#define NUM_QUAD_PLANE_VERTICES 6

#define NUMBER_OF_PLANES 3

int g_syncCubes = 1;

// UDPClient_update_data_Cubes.cpp
void UpdateDataCubesold(std::vector<Cube>& cubes, std::vector<CubeGraphicsData>& cubegraphicsdata)
{

    int iCubeIndex = 0;
    int iCubeMax = cubes.size();

    // 36 * 5 = 180

    // 5 * 6 * 3 = 90
    // 270

   // int i = 270;
   // 

    // wtf is this? a guess, it will override everything on top of this!!.
  //  int i = (NUM_CUBE_SIDES * NUM_QUAD_PLANE_VERTICES * iNumVertexAttributes) + (NUM_QUAD_PLANE_VERTICES * iNumVertexAttributes * NUMBER_OF_PLANES);
    int i = 0;

    //for (int i = 54; i < mainVertices.size() / 5; i += 5*6)

    //printf("i: %d ,mainVertices.size() %d\n ", i, mainVertices.size());

    if (iCubeIndex < iCubeMax && i < mainVertices.size())
    {
        while (iCubeIndex < iCubeMax && i < mainVertices.size())
        {
            i = cubegraphicsdata[iCubeIndex].mainVerticesIndex;

            float x = cubes[iCubeIndex].position.x;
            float y = cubes[iCubeIndex].position.y;
            float z = cubes[iCubeIndex].position.z;

            float cubevvtype = (float)cubes[iCubeIndex].iHighLight[0];

            //     printf("\ncubes[iCubeIndex].position.x: %f, cubes[iCubeIndex].position.y: %f , cubes[iCubeIndex].position.z: %f\n\n ", cubes[iCubeIndex].position.x, cubes[iCubeIndex].position.y, cubes[iCubeIndex].position.z);
                 //  mainVertices[i] = -0.5f + x;

            mainVertices[i] = -0.5f + x;    mainVertices[i + 1] = -0.5f + y;    mainVertices[i + 2] = -0.5f + z;   mainVertices[i + 3] = 0.0f;    mainVertices[i + 4] = 0.0f;  mainVertices[i + 5] = cubevvtype;

            //   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            mainVertices[i + 6] = 0.5f + x;    mainVertices[i + 7] = -0.5f + y;    mainVertices[i + 8] = -0.5f + z;   mainVertices[i + 9] = 1.0f;    mainVertices[i + 10] = 0.0f;  mainVertices[i + 11] = cubevvtype;



            //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 12] = 0.5f + x;    mainVertices[i + 13] = 0.5f + y;    mainVertices[i + 14] = -0.5f + z;   mainVertices[i + 15] = 1.0f;    mainVertices[i + 16] = 1.0f;  mainVertices[i + 17] = cubevvtype;

            // triangle 1
         //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 18] = 0.5f + x;    mainVertices[i + 19] = 0.5f + y;    mainVertices[i + 20] = -0.5f + z;   mainVertices[i + 21] = 0.0f;    mainVertices[i + 22] = 0.0f;  mainVertices[i + 23] = cubevvtype;

            // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 24] = -0.5f + x;    mainVertices[i + 25] = 0.5f + y;    mainVertices[i + 26] = -0.5f + z;   mainVertices[i + 27] = 0.0f;    mainVertices[i + 28] = 0.0f; mainVertices[i + 29] = cubevvtype;

            // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            mainVertices[i + 30] = -0.5f + x;    mainVertices[i + 31] = -0.5f + y;    mainVertices[i + 32] = -0.5f + z;   mainVertices[i + 33] = 0.0f;    mainVertices[i + 34] = 0.0f; mainVertices[i + 35] = cubevvtype;

            // face 1
        // triangle 2
       // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 36] = -0.5f + x;    mainVertices[i + 37] = -0.5f + y;    mainVertices[i + 38] = 0.5f + z;   mainVertices[i + 39] = 0.0f;    mainVertices[i + 40] = 0.0f;  mainVertices[i + 41] = cubevvtype;

            //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 42] = 0.5f + x;    mainVertices[i + 43] = -0.5f + y;    mainVertices[i + 44] = 0.5f + z;   mainVertices[i + 45] = 0.0f;    mainVertices[i + 46] = 0.0f;  mainVertices[i + 47] = cubevvtype;

            //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            mainVertices[i + 48] = 0.5f + x;    mainVertices[i + 49] = 0.5f + y;    mainVertices[i + 50] = 0.5f + z;   mainVertices[i + 51] = 0.0f;    mainVertices[i + 52] = 0.0f;  mainVertices[i + 53] = cubevvtype;

            // triangle 3
            // 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            mainVertices[i + 54] = 0.5f + x;    mainVertices[i + 55] = 0.5f + y;    mainVertices[i + 56] = 0.5f + z;   mainVertices[i + 57] = 0.0f;    mainVertices[i + 58] = 0.0f; mainVertices[i + 59] = cubevvtype;


            //-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            mainVertices[i + 60] = -0.5f + x;    mainVertices[i + 61] = 0.5f + y;    mainVertices[i + 62] = 0.5f + z;   mainVertices[i + 63] = 0.0f;    mainVertices[i + 64] = 0.0f; mainVertices[i + 65] = cubevvtype;

            //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 66] = -0.5f + x;    mainVertices[i + 67] = -0.5f + y;    mainVertices[i + 68] = 0.5f + z;   mainVertices[i + 69] = 0.0f;    mainVertices[i + 70] = 0.0f; mainVertices[i + 71] = cubevvtype;

            //face 2
         // triangle 4   
        //-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 72] = -0.5f + x;    mainVertices[i + 73] = 0.5f + y;    mainVertices[i + 74] = 0.5f + z;   mainVertices[i + 75] = 0.0f;    mainVertices[i + 76] = 0.0f; mainVertices[i + 77] = cubevvtype;

            //-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 78] = -0.5f + x;    mainVertices[i + 79] = 0.5f + y;    mainVertices[i + 80] = -0.5f + z;   mainVertices[i + 81] = 0.0f;    mainVertices[i + 82] = 0.0f; mainVertices[i + 83] = cubevvtype;

            //-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 84] = -0.5f + x;    mainVertices[i + 85] = -0.5f + y;    mainVertices[i + 86] = -0.5f + z;   mainVertices[i + 87] = 0.0f;    mainVertices[i + 88] = 0.0f; mainVertices[i + 89] = cubevvtype;

            // triangle 5
        //-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 90] = -0.5f + x;    mainVertices[i + 91] = -0.5f + y;    mainVertices[i + 92] = -0.5f + z;   mainVertices[i + 93] = 0.0f;    mainVertices[i + 94] = 0.0f; mainVertices[i + 95] = cubevvtype;

            //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 96] = -0.5f + x;    mainVertices[i + 97] = -0.5f + y;    mainVertices[i + 98] = 0.5f + z;   mainVertices[i + 99] = 0.0f;    mainVertices[i + 100] = 0.0f;  mainVertices[i + 101] = cubevvtype;

            //-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 102] = -0.5f + x;    mainVertices[i + 103] = 0.5f + y;    mainVertices[i + 104] = 0.5f + z;   mainVertices[i + 105] = 0.0f;    mainVertices[i + 106] = 0.0f; mainVertices[i + 107] = cubevvtype;

            //face 3
            // triangle 6

        // 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 108] = 0.5f + x;    mainVertices[i + 109] = 0.5f + y;    mainVertices[i + 110] = 0.5f + z;   mainVertices[i + 111] = 0.0f;    mainVertices[i + 112] = 0.0f; mainVertices[i + 113] = cubevvtype;

            // 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 114] = 0.5f + x;    mainVertices[i + 115] = 0.5f + y;    mainVertices[i + 116] = -0.5f + z;   mainVertices[i + 117] = 0.0f;    mainVertices[i + 118] = 0.0f; mainVertices[i + 119] = cubevvtype;


            // 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 120] = 0.5f + x;    mainVertices[i + 121] = -0.5f + y;    mainVertices[i + 122] = -0.5f + z;   mainVertices[i + 123] = 0.0f;    mainVertices[i + 124] = 0.0f;  mainVertices[i + 125] = cubevvtype;

            // triangle 7
       // 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 126] = 0.5f + x;    mainVertices[i + 127] = -0.5f + y;    mainVertices[i + 128] = -0.5f + z;   mainVertices[i + 129] = 0.0f;    mainVertices[i + 130] = 0.0f; mainVertices[i + 131] = cubevvtype;

            //  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 132] = 0.5f + x;    mainVertices[i + 133] = -0.5f + y;    mainVertices[i + 134] = 0.5f + z;   mainVertices[i + 135] = 0.0f;    mainVertices[i + 136] = 0.0f; mainVertices[i + 137] = cubevvtype;

            //   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 138] = 0.5f + x;    mainVertices[i + 139] = 0.5f + y;    mainVertices[i + 140] = 0.5f + z;   mainVertices[i + 141] = 0.0f;    mainVertices[i + 142] = 0.0f; mainVertices[i + 143] = cubevvtype;

            //face 4
            // triangle 8
     //  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 144] = -0.5f + x;    mainVertices[i + 145] = -0.5f + y;    mainVertices[i + 146] = -0.5f + z;   mainVertices[i + 147] = 0.0f;    mainVertices[i + 148] = 0.0f;  mainVertices[i + 149] = cubevvtype;

            // 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 150] = 0.5f + x;    mainVertices[i + 151] = -0.5f + y;    mainVertices[i + 152] = -0.5f + z;   mainVertices[i + 153] = 0.0f;    mainVertices[i + 154] = 0.0f;  mainVertices[i + 155] = cubevvtype;

            //0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 156] = 0.5f + x;    mainVertices[i + 157] = -0.5f + y;    mainVertices[i + 158] = 0.5f + z;   mainVertices[i + 159] = 0.0f;    mainVertices[i + 160] = 0.0f;  mainVertices[i + 161] = cubevvtype;

            // triangle 9

        //    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 162] = 0.5f + x;    mainVertices[i + 163] = -0.5f + y;    mainVertices[i + 164] = 0.5f + z;   mainVertices[i + 165] = 0.0f;    mainVertices[i + 166] = 0.0f; mainVertices[i + 167] = cubevvtype;

            // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 168] = -0.5f + x;    mainVertices[i + 169] = -0.5f + y;    mainVertices[i + 170] = 0.5f + z;   mainVertices[i + 171] = 0.0f;    mainVertices[i + 172] = 0.0f; mainVertices[i + 173] = cubevvtype;

            // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 174] = -0.5f + x;    mainVertices[i + 175] = -0.5f + y;    mainVertices[i + 176] = -0.5f + z;   mainVertices[i + 177] = 0.0f;    mainVertices[i + 178] = 0.0f; mainVertices[i + 179] = cubevvtype;

            //face 5
            //triangle 10
      // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 180] = -0.5f + x;    mainVertices[i + 181] = 0.5f + y;    mainVertices[i + 182] = -0.5f + z;   mainVertices[i + 183] = 0.0f;    mainVertices[i + 184] = 0.0f;  mainVertices[i + 185] = cubevvtype;

            //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 186] = 0.5f + x;    mainVertices[i + 187] = 0.5f + y;    mainVertices[i + 188] = -0.5f + z;   mainVertices[i + 189] = 0.0f;    mainVertices[i + 190] = 0.0f;  mainVertices[i + 191] = cubevvtype;

            //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 192] = 0.5f + x;    mainVertices[i + 193] = 0.5f + y;    mainVertices[i + 194] = 0.5f + z;   mainVertices[i + 195] = 0.0f;    mainVertices[i + 196] = 0.0f;  mainVertices[i + 197] = cubevvtype;
            //triangle 11
       //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 198] = 0.5f + x;    mainVertices[i + 199] = 0.5f + y;    mainVertices[i + 200] = 0.5f + z;   mainVertices[i + 201] = 0.0f;    mainVertices[i + 202] = 0.0f;  mainVertices[i + 203] = cubevvtype;

            // -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 204] = -0.5f + x;    mainVertices[i + 205] = 0.5f + y;    mainVertices[i + 206] = 0.5f + z;   mainVertices[i + 207] = 0.0f;    mainVertices[i + 208] = 0.0f;  mainVertices[i + 209] = cubevvtype;

            // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            mainVertices[i + 210] = -0.5f + x;    mainVertices[i + 211] = 0.5f + y;    mainVertices[i + 212] = -0.5f + z;   mainVertices[i + 213] = 0.0f;    mainVertices[i + 214] = 0.0f; mainVertices[i + 215] = cubevvtype;
            /// 6*6*6*
           //  216



            i += iNumVertexAttributes * NUM_CUBE_SIDES * NUM_QUAD_PLANE_VERTICES;
            // i += 6 * 6 * 6; // = 216
            iCubeIndex++;

        }
        // exit(0);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

       // glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data());
        GLenum err = glGetError(); if (err != GL_NO_ERROR) {
            printf("OpenGL Error: %x\n", err);
            exit(4);
        }

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);



        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

}

void UpdateDataCubes(std::vector<Cube>& cubes, std::vector<CubeGraphicsData>& cubegraphicsdata)
{

    int iCubeIndex = 0;
    int iCubeMax = cubes.size();

    // 36 * 5 = 180

    // 5 * 6 * 3 = 90
    // 270

   // int i = 270;
   // 

    // wtf is this? a guess, it will override everything on top of this!!.
  //  int i = (NUM_CUBE_SIDES * NUM_QUAD_PLANE_VERTICES * iNumVertexAttributes) + (NUM_QUAD_PLANE_VERTICES * iNumVertexAttributes * NUMBER_OF_PLANES);
    int i = 0;

    //for (int i = 54; i < mainVertices.size() / 5; i += 5*6)

    //printf("i: %d ,mainVertices.size() %d\n ", i, mainVertices.size());

    if (iCubeIndex < iCubeMax && i < mainVertices.size())
    {
        while (iCubeIndex < iCubeMax && i < mainVertices.size())
        {
            i = cubegraphicsdata[iCubeIndex].mainVerticesIndex;

            float x = cubes[iCubeIndex].position.x;
            float y = cubes[iCubeIndex].position.y;
            float z = cubes[iCubeIndex].position.z;

            float cubevvtype = (float)cubes[iCubeIndex].iHighLight[0];

            //  printf("\ncubes[iCubeIndex].position.x: %f, cubes[iCubeIndex].position.y: %f , cubes[iCubeIndex].position.z: %f\n\n ", cubes[iCubeIndex].position.x, cubes[iCubeIndex].position.y, cubes[iCubeIndex].position.z);
              //  mainVertices[i] = -0.5f + x;

            mainVertices[i] = -0.5f + x;    mainVertices[i + 1] = -0.5f + y;    mainVertices[i + 2] = -0.5f + z;   mainVertices[i + 3] = 0.0f;    mainVertices[i + 4] = 0.0f; // mainVertices[i + 5] = cubevvtype;

            //   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            mainVertices[i + 6] = 0.5f + x;    mainVertices[i + 7] = -0.5f + y;    mainVertices[i + 8] = -0.5f + z;   mainVertices[i + 9] = 1.0f;    mainVertices[i + 10] = 0.0f; // mainVertices[i + 11] = cubevvtype;



            //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 12] = 0.5f + x;    mainVertices[i + 13] = 0.5f + y;    mainVertices[i + 14] = -0.5f + z;   mainVertices[i + 15] = 1.0f;    mainVertices[i + 16] = 1.0f; // mainVertices[i + 17] = cubevvtype;

            // triangle 1
         //   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 18] = 0.5f + x;    mainVertices[i + 19] = 0.5f + y;    mainVertices[i + 20] = -0.5f + z;   mainVertices[i + 21] = 0.0f;    mainVertices[i + 22] = 0.0f; // mainVertices[i + 23] = cubevvtype;

            // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 24] = -0.5f + x;    mainVertices[i + 25] = 0.5f + y;    mainVertices[i + 26] = -0.5f + z;   mainVertices[i + 27] = 0.0f;    mainVertices[i + 28] = 0.0f;// mainVertices[i + 29] = cubevvtype;

            // -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            mainVertices[i + 30] = -0.5f + x;    mainVertices[i + 31] = -0.5f + y;    mainVertices[i + 32] = -0.5f + z;   mainVertices[i + 33] = 0.0f;    mainVertices[i + 34] = 0.0f;// mainVertices[i + 35] = cubevvtype;

            // face 1
        // triangle 2
       // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 36] = -0.5f + x;    mainVertices[i + 37] = -0.5f + y;    mainVertices[i + 38] = 0.5f + z;   mainVertices[i + 39] = 0.0f;    mainVertices[i + 40] = 0.0f; // mainVertices[i + 41] = cubevvtype;

            //  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 42] = 0.5f + x;    mainVertices[i + 43] = -0.5f + y;    mainVertices[i + 44] = 0.5f + z;   mainVertices[i + 45] = 0.0f;    mainVertices[i + 46] = 0.0f;//  mainVertices[i + 47] = cubevvtype;

            //  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            mainVertices[i + 48] = 0.5f + x;    mainVertices[i + 49] = 0.5f + y;    mainVertices[i + 50] = 0.5f + z;   mainVertices[i + 51] = 0.0f;    mainVertices[i + 52] = 0.0f;//  mainVertices[i + 53] = cubevvtype;

            // triangle 3
            // 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            mainVertices[i + 54] = 0.5f + x;    mainVertices[i + 55] = 0.5f + y;    mainVertices[i + 56] = 0.5f + z;   mainVertices[i + 57] = 0.0f;    mainVertices[i + 58] = 0.0f;// mainVertices[i + 59] = cubevvtype;


            //-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            mainVertices[i + 60] = -0.5f + x;    mainVertices[i + 61] = 0.5f + y;    mainVertices[i + 62] = 0.5f + z;   mainVertices[i + 63] = 0.0f;    mainVertices[i + 64] = 0.0f;// mainVertices[i + 65] = cubevvtype;

            //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 66] = -0.5f + x;    mainVertices[i + 67] = -0.5f + y;    mainVertices[i + 68] = 0.5f + z;   mainVertices[i + 69] = 0.0f;    mainVertices[i + 70] = 0.0f;// mainVertices[i + 71] = cubevvtype;

            //face 2
         // triangle 4   
        //-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 72] = -0.5f + x;    mainVertices[i + 73] = 0.5f + y;    mainVertices[i + 74] = 0.5f + z;   mainVertices[i + 75] = 0.0f;    mainVertices[i + 76] = 0.0f;// mainVertices[i + 77] = cubevvtype;

            //-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 78] = -0.5f + x;    mainVertices[i + 79] = 0.5f + y;    mainVertices[i + 80] = -0.5f + z;   mainVertices[i + 81] = 0.0f;    mainVertices[i + 82] = 0.0f; // mainVertices[i + 83] = cubevvtype;

            //-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 84] = -0.5f + x;    mainVertices[i + 85] = -0.5f + y;    mainVertices[i + 86] = -0.5f + z;   mainVertices[i + 87] = 0.0f;    mainVertices[i + 88] = 0.0f;// mainVertices[i + 89] = cubevvtype;

            // triangle 5
        //-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 90] = -0.5f + x;    mainVertices[i + 91] = -0.5f + y;    mainVertices[i + 92] = -0.5f + z;   mainVertices[i + 93] = 0.0f;    mainVertices[i + 94] = 0.0f; // mainVertices[i + 95] = cubevvtype;

            //-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 96] = -0.5f + x;    mainVertices[i + 97] = -0.5f + y;    mainVertices[i + 98] = 0.5f + z;   mainVertices[i + 99] = 0.0f;    mainVertices[i + 100] = 0.0f; // mainVertices[i + 101] = cubevvtype;

            //-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 102] = -0.5f + x;    mainVertices[i + 103] = 0.5f + y;    mainVertices[i + 104] = 0.5f + z;   mainVertices[i + 105] = 0.0f;    mainVertices[i + 106] = 0.0f; // mainVertices[i + 107] = cubevvtype;

            //face 3
            // triangle 6

        // 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 108] = 0.5f + x;    mainVertices[i + 109] = 0.5f + y;    mainVertices[i + 110] = 0.5f + z;   mainVertices[i + 111] = 0.0f;    mainVertices[i + 112] = 0.0f;// mainVertices[i + 113] = cubevvtype;

            // 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 114] = 0.5f + x;    mainVertices[i + 115] = 0.5f + y;    mainVertices[i + 116] = -0.5f + z;   mainVertices[i + 117] = 0.0f;    mainVertices[i + 118] = 0.0f;//  mainVertices[i + 119] = cubevvtype;


            // 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 120] = 0.5f + x;    mainVertices[i + 121] = -0.5f + y;    mainVertices[i + 122] = -0.5f + z;   mainVertices[i + 123] = 0.0f;    mainVertices[i + 124] = 0.0f;  // mainVertices[i + 125] = cubevvtype;

            // triangle 7
       // 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 126] = 0.5f + x;    mainVertices[i + 127] = -0.5f + y;    mainVertices[i + 128] = -0.5f + z;   mainVertices[i + 129] = 0.0f;    mainVertices[i + 130] = 0.0f;//  mainVertices[i + 131] = cubevvtype;

            //  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 132] = 0.5f + x;    mainVertices[i + 133] = -0.5f + y;    mainVertices[i + 134] = 0.5f + z;   mainVertices[i + 135] = 0.0f;    mainVertices[i + 136] = 0.0f; // mainVertices[i + 137] = cubevvtype;

            //   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 138] = 0.5f + x;    mainVertices[i + 139] = 0.5f + y;    mainVertices[i + 140] = 0.5f + z;   mainVertices[i + 141] = 0.0f;    mainVertices[i + 142] = 0.0f;//  mainVertices[i + 143] = cubevvtype;

            //face 4
            // triangle 8
     //  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 144] = -0.5f + x;    mainVertices[i + 145] = -0.5f + y;    mainVertices[i + 146] = -0.5f + z;   mainVertices[i + 147] = 0.0f;    mainVertices[i + 148] = 0.0f; // mainVertices[i + 149] = cubevvtype;

            // 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 150] = 0.5f + x;    mainVertices[i + 151] = -0.5f + y;    mainVertices[i + 152] = -0.5f + z;   mainVertices[i + 153] = 0.0f;    mainVertices[i + 154] = 0.0f; // mainVertices[i + 155] = cubevvtype;

            //0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 156] = 0.5f + x;    mainVertices[i + 157] = -0.5f + y;    mainVertices[i + 158] = 0.5f + z;   mainVertices[i + 159] = 0.0f;    mainVertices[i + 160] = 0.0f; // mainVertices[i + 161] = cubevvtype;

            // triangle 9

        //    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 162] = 0.5f + x;    mainVertices[i + 163] = -0.5f + y;    mainVertices[i + 164] = 0.5f + z;   mainVertices[i + 165] = 0.0f;    mainVertices[i + 166] = 0.0f; // mainVertices[i + 167] = cubevvtype;

            // -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 168] = -0.5f + x;    mainVertices[i + 169] = -0.5f + y;    mainVertices[i + 170] = 0.5f + z;   mainVertices[i + 171] = 0.0f;    mainVertices[i + 172] = 0.0f; // mainVertices[i + 173] = cubevvtype;

            // -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 174] = -0.5f + x;    mainVertices[i + 175] = -0.5f + y;    mainVertices[i + 176] = -0.5f + z;   mainVertices[i + 177] = 0.0f;    mainVertices[i + 178] = 0.0f; // mainVertices[i + 179] = cubevvtype;

            //face 5
            //triangle 10
      // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            mainVertices[i + 180] = -0.5f + x;    mainVertices[i + 181] = 0.5f + y;    mainVertices[i + 182] = -0.5f + z;   mainVertices[i + 183] = 0.0f;    mainVertices[i + 184] = 0.0f; // mainVertices[i + 185] = cubevvtype;

            //  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            mainVertices[i + 186] = 0.5f + x;    mainVertices[i + 187] = 0.5f + y;    mainVertices[i + 188] = -0.5f + z;   mainVertices[i + 189] = 0.0f;    mainVertices[i + 190] = 0.0f; // mainVertices[i + 191] = cubevvtype;

            //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 192] = 0.5f + x;    mainVertices[i + 193] = 0.5f + y;    mainVertices[i + 194] = 0.5f + z;   mainVertices[i + 195] = 0.0f;    mainVertices[i + 196] = 0.0f; //  mainVertices[i + 197] = cubevvtype;
            //triangle 11
       //  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            mainVertices[i + 198] = 0.5f + x;    mainVertices[i + 199] = 0.5f + y;    mainVertices[i + 200] = 0.5f + z;   mainVertices[i + 201] = 0.0f;    mainVertices[i + 202] = 0.0f; // mainVertices[i + 203] = cubevvtype;

            // -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            mainVertices[i + 204] = -0.5f + x;    mainVertices[i + 205] = 0.5f + y;    mainVertices[i + 206] = 0.5f + z;   mainVertices[i + 207] = 0.0f;    mainVertices[i + 208] = 0.0f; // mainVertices[i + 209] = cubevvtype;

            // -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            mainVertices[i + 210] = -0.5f + x;    mainVertices[i + 211] = 0.5f + y;    mainVertices[i + 212] = -0.5f + z;   mainVertices[i + 213] = 0.0f;    mainVertices[i + 214] = 0.0f; // mainVertices[i + 215] = cubevvtype;
            /// 6*6*6*
           //  216



         //   i += iNumVertexAttributes * NUM_CUBE_SIDES * NUM_QUAD_PLANE_VERTICES;
            // i += 6 * 6 * 6; // = 216
            iCubeIndex++;

        }
        // exit(0);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

       // glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, mainVertices.size() * sizeof(float), mainVertices.data());
        GLenum err = glGetError(); if (err != GL_NO_ERROR) {
            printf("OpenGL Error: %x\n", err);
            exit(4);
        }

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);



        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

}

