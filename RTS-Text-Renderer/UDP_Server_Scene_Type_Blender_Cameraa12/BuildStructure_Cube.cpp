#include "BuildStructure_Cube.h"




extern std::vector<float> mainVertices;
extern GLuint VAO;

extern GLuint VBO;

BuildStructure_Cube::BuildStructure_Cube()
{
    // make a invisiable cube and then check GameStateBuildCast for operations
    NumberOfVertsInObject = AddCubeBuild(0.0f, 0.0f, 0.0f, 2.0);

    m_CreateSpawnPacketSender = new CreateSpawnPacketSender();

    placement_position.x = 0.0f;
    placement_position.y = 0.0f;
    placement_position.z = 0.0f;
}


BuildStructure_Cube::~BuildStructure_Cube()
{


}

int BuildStructure_Cube::AddCubeBuild(float x, float y, float z, float width)
{
    /*
    Cube* newCube = (Cube*)malloc(sizeof(Cube));

    newCube->halfSize = width/ 2.0f;
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
    /*
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
    */
    // mainVerticesIndex


    // The temporary 'newCube' object is automatically destroyed when it goes out of scope.
    // The vector 'cubes' now holds its own copy.

    CastCubeIndex = mainVertices.size();


    // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
   // float vertices[] = {
   // -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
   // // face 0
       // triangle 0

    float halfSize = width / 2.0f;
    const float vvtype = 533.0f;

    // Front face (-Z)
    // Triangle 1
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-left
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-right
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-right

    // Triangle 2
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-right
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-left
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-left

    // Back face (+Z)
    // Triangle 1
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-right (looking from front)
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-left (looking from front)
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-left (looking from front)

    // Triangle 2
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-left (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-right (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-right (looking from front)

    // Right face (+X)
    // Triangle 1
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-left
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-right
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-right

    // Triangle 2
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-right
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-left
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-left

    // Left face (-X)
    // Triangle 1
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-left (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-right (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-right (looking from front)

    // Triangle 2
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-right (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Top-left (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Bottom-left (looking from front)

    // Top face (+Y)
    // Triangle 1
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Bottom-left
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Bottom-right
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Top-right

    // Triangle 2
    mainVertices.push_back(halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Top-right
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Top-left
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Bottom-left

    // Bottom face (-Y)
    // Triangle 1
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Top-left (looking from front)
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Top-right (looking from front)
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Bottom-right (looking from front)

    // Triangle 2
    mainVertices.push_back(halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Bottom-right (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(vvtype); // Bottom-left (looking from front)
    mainVertices.push_back(-halfSize + x); mainVertices.push_back(-halfSize + y); mainVertices.push_back(-halfSize + z); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(vvtype); // Top-left (looking from front)

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
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  //  glEnableVertexAttribArray(0);
    // texture coord attribute
  //  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  //  glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 36;
}

void BuildStructure_Cube::UpdateCastLocationCube(float x, float y, float z, float width)

//void   UpdateCube(Cube newCube)
{
    int iNumVertexAttributes = 6;

    // need a map for object_id, or id of cube to cubegraphicsdata index, for now assuming user didn't locally spawn cubes
  //  int iCubeIndex = newCube.id;
    int i = CastCubeIndex; // cubeGraphicsData[iCubeIndex - 1].mainVerticesIndex;// no 
    /*
    float x = newCube.position.x;
    float y = newCube.position.y;
    float z = newCube.position.z;

    cubes[iCubeIndex - 1].position.x = newCube.position.x;
    cubes[iCubeIndex - 1].position.y = newCube.position.y;
    cubes[iCubeIndex - 1].position.z = newCube.position.z;


    cubes[iCubeIndex - 1].velocity.x = newCube.velocity.x;
    cubes[iCubeIndex - 1].velocity.y = newCube.velocity.y;
    cubes[iCubeIndex - 1].velocity.z = newCube.velocity.z;



    cubes[iCubeIndex - 1].iHighLight[0] = newCube.iHighLight[0];
    cubes[iCubeIndex - 1].iHighLight[1] = newCube.iHighLight[1];
    cubes[iCubeIndex - 1].iHighLight[2] = newCube.iHighLight[2];
    cubes[iCubeIndex - 1].iHighLight[3] = newCube.iHighLight[3];


    cubes[iCubeIndex - 1].halfSize = newCube.halfSize;
    cubes[iCubeIndex - 1].iRenderType = newCube.iRenderType;

    */
    //  float halfSize;

    //  uint32_t iRenderType;
    float vvtype = 534.0f;

    float cubevvtype = vvtype;// (float)cubes[iCubeIndex - 1].iHighLight[0];

    //     printf("\ncubes[iCubeIndex].position.x: %f, cubes[iCubeIndex].position.y: %f , cubes[iCubeIndex].position.z: %f\n\n ", x, y, z);
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

#define NUM_CUBE_SIDES 6
#define NUM_QUAD_PLANE_VERTICES 6
   // i += iNumVertexAttributes * NUM_CUBE_SIDES * NUM_QUAD_PLANE_VERTICES;
    int iSizeOfCubeVerts = iNumVertexAttributes * NUM_CUBE_SIDES * NUM_QUAD_PLANE_VERTICES;;
    // i += 6 * 6 * 6; // = 216
//iCubeIndex++;


// exit(0);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

    // glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);
    //  glBufferSubData(GL_ARRAY_BUFFER, iOffSet * sizeof(float), iSize * sizeof(float), vertices44);
    glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(float), iSizeOfCubeVerts * sizeof(float), mainVertices.data() + i);
    GLenum err = glGetError(); if (err != GL_NO_ERROR) {
        printf("OpenGL Error: %x\n", err);
        exit(20);
    }

    // position attribute
 //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
 //   glEnableVertexAttribArray(0);
    // texture coord attribute
 //   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

extern unsigned int g_Width;
extern unsigned int g_Height;
extern int iTypeCamera;

extern BaseCameraClass* basecamera;
extern BlenderCameraClass* blendercamera;
extern BlenderCameraClass2* blendercamera2;
extern BlenderCameraClass3* blendercamera3;
extern BlenderCameraClass4* blendercamera4;
extern BlenderCameraClass5* blendercamera5;
extern BlenderCameraClass6* blendercamera6;
extern BlenderCameraClass7* blendercamera7;

//ColoQuatCamera* g_ColoQuatCamera;
extern ColoQuatCamera* quatcamera;

extern Cursor_UI_Draw* cursor_ui_draw;

void BuildStructure_Cube::mouse_callback(GLFWwindow* window, float xposIn, float yposIn)
{
    // ray cast
  //  std::cout << "Fire Ray GLFW_MOUSE_BUTTON_RIGHT" << std::endl;
    // search in glm for this:
// https://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/raytri/
    // to reverse engineer the intersection code
   // mouse_x = cursor_ui_draw->MouseVirtualX * g_Width;
  //  mouse_y = cursor_ui_draw->MouseVirtualY * g_Height;

    int mouse_x2 = ((cursor_ui_draw->MouseVirtualX + 1.0) * (g_Width / 2));
    int mouse_y2 = g_Height - ((cursor_ui_draw->MouseVirtualY + 1.0) * (g_Height / 2));


    // printf("cursor_ui_draw->MouseVirtualX %f, cursor_ui_draw->MouseVirtualY: %f\n", cursor_ui_draw->MouseVirtualX, cursor_ui_draw->MouseVirtualY);
    // printf("mouse_x2 %d, mouse_y2: %d\n", mouse_x2, mouse_y2);
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
        my_ray = create_ray_from_mouse_unproject(mouse_x2, mouse_y2, g_Width, g_Height, blendercamera7->GetViewMatrix(), blendercamera7->GetProjectionMatrix());
    }

    if (iTypeCamera == 9)
    {
        //  blendercamera->ProcessKeyboard(movementtype, deltaTime);
        quatcamera->updateCameraMatrixes();
        //    printf("my_ray = quatcamera\n");
        my_ray = create_ray_from_mouse(mouse_x2, mouse_y2, g_Width, g_Height, quatcamera->GetGLMViewMatrix(), quatcamera->GetGLMProjectionMatrix());
    }

    glm::vec4 rayColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 startPos = my_ray.origin;

    //   glm::vec3 endPos = my_ray.origin + my_ray.direction;
    glm::vec3 direction = my_ray.direction;

    float width = 0.01f;
    // int iNumberVertexesAdded = AddCubeLine(startPos,  endPos,  width, rayColor);

    //int iNumberVertexesAdded = AddCubeLine2(startPos, direction, width, rayColor);


    //  checkMouseClick(create_ray_from_mouse
 //   glm::vec3 triangleVertice1 = glm::vec3(1.5, 1.5, 1.5f);
 //   glm::vec3 triangleVertice2 = glm::vec3(1.5, -1.5, 1.5f);
  //  glm::vec3 triangleVertice3 = glm::vec3(.75, 0.0f, 1.5f);

    bool Didhit = false;
    float t2 = 0.0f;

    // for (int iCubeIndex = 0; iCubeIndex < g_pGoshaRayIntersectionPlaneManager->m_intersection_planes.size(); iCubeIndex++)
    {
        //   int iCubeVerticeIndex = g_pGoshaRayIntersectionPlaneManager->m_intersection_planes[iCubeIndex]->iPlaneIndex;//cubeGraphicsData[iCubeIndex].mainVerticesIndex;


        //   glm::vec3 triangleVertice1 = glm::vec3(mainVertices[iCubeVerticeIndex], mainVertices[iCubeVerticeIndex + 1], mainVertices[iCubeVerticeIndex + 2]);
        //   glm::vec3 triangleVertice2 = glm::vec3(mainVertices[iCubeVerticeIndex + 6], mainVertices[iCubeVerticeIndex + 7], mainVertices[iCubeVerticeIndex + 8]);
        //   glm::vec3 triangleVertice3 = glm::vec3(mainVertices[iCubeVerticeIndex + 12], mainVertices[iCubeVerticeIndex + 13], mainVertices[iCubeVerticeIndex + 14]);
        glm::vec3 triangleVertice1 = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 triangleVertice2 = glm::vec3(100.0f, 0.0f, -1.0f);
        glm::vec3 triangleVertice3 = glm::vec3(0.0f, 50.0f, -1.0f);
        //  glm::vec3 g_triangleVertice1 = glm::vec3(1.5, 1.5, 1.5f);
//  glm::vec3 g_triangleVertice2 = glm::vec3(1.5, -1.5, 1.5f);
//  glm::vec3 g_triangleVertice3 = glm::vec3(.75, 0.0f, 1.5f);

       //AddTriangleTest(triangleVertice1, triangleVertice2, triangleVertice3);//add a duplicate model where ray hit


        glm::vec2 vec2return = checkMouseClick2(my_ray, triangleVertice1, triangleVertice2, triangleVertice3, Didhit, t2);

        //    std::cout << "Ray Origin: (" << my_ray.origin.x << ", " << my_ray.origin.y << ", " << my_ray.origin.z << ")" << std::endl;
         //   std::cout << "Ray Direction: (" << my_ray.direction.x << ", " << my_ray.direction.y << ", " << my_ray.direction.z << ")" << std::endl;

        //    std::cout << "vec2return.g: (" << vec2return.g << std::endl;
         //   std::cout << "vec2return.length: (" << vec2return.length << std::endl;

        if (Didhit) {
            // Calculate the world space intersection point using the ray's parametric equation:
            // P = Origin + Direction * t
            glm::vec3 intersection_point = my_ray.origin + my_ray.direction * t2;

            //    std::cout << "Ray HIT the triangle!" << std::endl;
            //    std::cout << "Intersection Point: ("
            //        << intersection_point.x << ", "
            //        << intersection_point.y << ", "
            //        << intersection_point.z << ")" << std::endl;

            placement_position.x = intersection_point.x;
            placement_position.y = intersection_point.y;
            placement_position.z = intersection_point.z;

            float cubeWidth = 0.25;


            //  int iNumVertsAlloc = AddIntersectionCube2(intersection_point.x, intersection_point.y, intersection_point.z, cubeWidth);
            //  int iNumberVertexesAdded2 = AddCubeLine3(startPos, direction, width, rayColor, t2);

            // UpdateCastLocationCube(intersection_point.x, intersection_point.y, intersection_point.z, 1.0f);
                //  UpdateCastLocationCube(intersection_point.x, intersection_point.y, intersection_point.z, t2);
            UpdateCastLocationCube(intersection_point.x, intersection_point.y, intersection_point.z, 1.0f);
            //     std::cout << "Hit Cube Index: ("
             //        << iCubeIndex
            //         << ");"
             //        << std::endl;

          //       mainVertices[iCubeVerticeIndex + 5] = 34.0f;
          //       mainVertices[iCubeVerticeIndex + 11] = 34.0f;
           //      mainVertices[iCubeVerticeIndex + 17] = 34.0f;

                 //    NetworkVector3 impulseAdd;
                  //   impulseAdd.x = direction.x;
                  //   impulseAdd.y = direction.y;
                  //   impulseAdd.z = direction.z;
                  //   float yPower = 10.0f;

            float xPower = 1.0f;
            float yPower = 1.0f;
            float zPower = 10.0f;
            //   cubes[iCubeIndex].velocity.x += direction.x * xPower;
             //  cubes[iCubeIndex].velocity.y += direction.y * yPower;
             //  cubes[iCubeIndex].velocity.z += direction.z * zPower;

        }
        else {
            //      std::cout << "Ray DID NOT HIT the triangle." << std::endl;
        }

    }//t

}
void BuildStructure_Cube::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (p_gCreateSpawnPacketSender)
    {
        p_gCreateSpawnPacketSender->mouse_button_callback(window, button, action, mods);
    }

}

BuildStructure_Cube* g_pBuildStructure_Cube = 0;;