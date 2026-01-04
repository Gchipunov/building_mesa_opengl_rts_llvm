// Paint on terrian, take dirt away.
// mine rocks
// water dams
// rivers flow

// https://creativemisconfiguration.wordpress.com/category/simcity-2000/#:~:text=Next%20I%20filled%20in%20the,square%205%C3%975%20grid.
    // Terrain.cpp

//#include "Terrain.h"
#include "Terrian_GridPlane.h"

extern std::vector<float> mainVertices;
extern GLuint VAO;
extern GLuint VBO;
extern int iNumVertexAttributes; // 6

Terrain::Terrain(int width, int height) : width(width), height(height) {
    tiles.resize(width, std::vector<Tile>(height, Tile(0, 0, 0.0f)));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            tiles[x][y] = Tile(x, y, 0.0f);
        }
    }
}

Terrain::~Terrain() {}

void Terrain::generateMesh() {
    vertices.clear();
    indices.clear();

    generateVertices();
    generateIndices();
}

void Terrain::generateVertices() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculate vertex positions for each tile corner
            float h = tiles[x][y].getHeight();
            vertices.push_back(glm::vec3(x, h, y));         // Top-left
            vertices.push_back(glm::vec3(x + 1, h, y));     // Top-right
            vertices.push_back(glm::vec3(x + 1, h, y + 1)); // Bottom-right
            vertices.push_back(glm::vec3(x, h, y + 1));     // Bottom-left
        }
    }
}

void Terrain::generateIndices() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Index of the top-left vertex of the current tile
            unsigned int startIndex = (y * width + x) * 4;

            // First triangle (top-left, top-right, bottom-right)
            indices.push_back(startIndex);
            indices.push_back(startIndex + 1);
            indices.push_back(startIndex + 2);

            // Second triangle (top-left, bottom-right, bottom-left)
            indices.push_back(startIndex);
            indices.push_back(startIndex + 2);
            indices.push_back(startIndex + 3);
        }
    }
}

Tile& Terrain::getTile(int x, int y) {
    return tiles[x][y];
}

void Terrain::updateTileHeight(int x, int y, float newHeight) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[x][y].setHeight(newHeight);
    }
}

void Terrain::updateTileType(int x, int y, TileType newType) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[x][y].setType(newType);
    }
}


// Assuming your mainVertices vector is a vector of floats.
// This is a simplified representation.
void push_vertex_plane(std::vector<float>& vertices, float x, float y, float z, float u, float v, float vvtype) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
    vertices.push_back(u);
    vertices.push_back(v);
    vertices.push_back(vvtype);
}
// -----------------------------------------------------
GoshaRayIntersectionPlane::GoshaRayIntersectionPlane()
{
}
GoshaRayIntersectionPlane::~GoshaRayIntersectionPlane()
{
}


int GoshaRayIntersectionPlane::CreatePlane(int CellIDx, int CellIDy) {
    iCellIDX = CellIDx;
    iCellIDY = CellIDy;
    float width = 1.0f;
    float height = 1.0f;

    float x = (float)CellIDx;
    float y = (float)CellIDy;


    float vvtype = 777.0f;

    //float divideHalf = 2.0f;
   // float divideHalf = 4.0f;
    float divideHalf = 2.1f;

    float halfWidth = width / divideHalf;
    float halfHeight = height / divideHalf;

    float v0x = x - halfWidth;
    float v1x = x + halfWidth;

    float v0y = y - halfHeight;
    float v1y = y + halfHeight;

    iPlaneIndex = mainVertices.size();
    // MouseWidth = width;
    // MouseHeight = height;
    x0 = v0x;
    x1 = v1x;

    y0 = v0y;
    y1 = v1y;

    z0 = -1.0f;
    z1 = -1.0f;
    z2 = -1.0f;
    z3 = -1.0f;

    uvx0 = 0.0f;
    uvx1 = 1.0f;

    uvy0 = 0.0f;
    uvy1 = 1.0f;

    // Quad 1:
// Vertex 1: Original bottom-left screen position. Should get the new bottom-left UVs.
//  push_vertex_plane(mainVertices, v1x, v0y, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
  ////	mainVertices.push_back(0); // Pushing vertex index for clarity

      // Vertex 2: Original bottom-right screen position. Should get the new bottom-right UVs.
//  push_vertex_plane(mainVertices, v1x, v1y, z, 1.0f, 0.0f, vvtype); // bottom-right screen position, new bottom-right UVs (from old bottom-left)
  ////	mainVertices.push_back(1);

      // Vertex 3: Original top-right screen position. Should get the new top-right UVs.
//  push_vertex_plane(mainVertices, v0x, v1y, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
  ////	mainVertices.push_back(2);

      // Quad 2:
      // Vertex 4: Original bottom-left screen position. Should get the new bottom-left UVs.
//   push_vertex_plane(mainVertices, v1x, v0y, z, 1.0f, 1.0f, vvtype); // bottom-left screen position, new bottom-left UVs (from old top-left)
   ////	mainVertices.push_back(0);

       // Vertex 5: Original top-right screen position. Should get the new top-right UVs.
//    push_vertex_plane(mainVertices, v0x, v1y, z, 0.0f, 0.0f, vvtype); // top-right screen position, new top-right UVs (from old bottom-right)
    ////	mainVertices.push_back(2);

        // Vertex 6: Original top-left screen position. Should get the new top-left UVs.
//    push_vertex_plane(mainVertices, v0x, v0y, z, 0.0f, 1.0f, vvtype); // top-left screen position, new top-left UVs (from old top-right)
    ////	mainVertices.push_back(3);
       // Quad 1 (Triangle 1): Vertices ordered as B, C, D (or similar winding)

   // Vertex 1 (B: Bottom-Right): Position v1x, v0y, **z1**
    push_vertex_plane(mainVertices, v1x, v0y, z1, uvx1, uvy1, vvtype);

    // Vertex 2 (C: Top-Right): Position v1x, v1y, **z2**
    push_vertex_plane(mainVertices, v1x, v1y, z2, uvx1, uvy0, vvtype);

    // Vertex 3 (D: Top-Left): Position v0x, v1y, **z3**
    push_vertex_plane(mainVertices, v0x, v1y, z3, uvx0, uvy0, vvtype);

    // Quad 2 (Triangle 2): Vertices ordered as B, D, A (or similar winding)

    // Vertex 4 (B: Bottom-Right): Position v1x, v0y, **z1**
    push_vertex_plane(mainVertices, v1x, v0y, z1, uvx1, uvy1, vvtype);

    // Vertex 5 (D: Top-Left): Position v0x, v1y, **z3**
    push_vertex_plane(mainVertices, v0x, v1y, z3, uvx0, uvy0, vvtype);

    // Vertex 6 (A: Bottom-Left): Position v0x, v0y, **z0**
    push_vertex_plane(mainVertices, v0x, v0y, z0, uvx0, uvy1, vvtype);

    return 6; // It's good practice to return a value if the function is non-void.
}
void GoshaRayIntersectionPlane::UpdatePlane() {
    //iPlaneIndex
     //iPlaneIndex
    mainVertices[iPlaneIndex] = x1;     mainVertices[iPlaneIndex + 1] = y0;  mainVertices[iPlaneIndex + 2] = z1;  mainVertices[iPlaneIndex + 3] = uvx1; mainVertices[iPlaneIndex + 4] = uvy1; mainVertices[iPlaneIndex + 5] = vvtype;
    mainVertices[iPlaneIndex + 6] = x1;  mainVertices[iPlaneIndex + 7] = y1;  mainVertices[iPlaneIndex + 8] = z2;  mainVertices[iPlaneIndex + 9] = uvx1; mainVertices[iPlaneIndex + 10] = uvy0; mainVertices[iPlaneIndex + 11] = vvtype;
    mainVertices[iPlaneIndex + 12] = x0;  mainVertices[iPlaneIndex + 13] = y1;  mainVertices[iPlaneIndex + 14] = z3;   mainVertices[iPlaneIndex + 15] = uvx0; mainVertices[iPlaneIndex + 16] = uvy0; mainVertices[iPlaneIndex + 17] = vvtype;

    mainVertices[iPlaneIndex + 18] = x1;  mainVertices[iPlaneIndex + 19] = y0;  mainVertices[iPlaneIndex + 20] = z1;   mainVertices[iPlaneIndex + 21] = uvx1; mainVertices[iPlaneIndex + 22] = uvy1; mainVertices[iPlaneIndex + 23] = vvtype;
    mainVertices[iPlaneIndex + 24] = x0;  mainVertices[iPlaneIndex + 25] = y1;  mainVertices[iPlaneIndex + 26] = z3;    mainVertices[iPlaneIndex + 27] = uvx0; mainVertices[iPlaneIndex + 28] = uvy0; mainVertices[iPlaneIndex + 29] = vvtype;
    mainVertices[iPlaneIndex + 30] = x0;  mainVertices[iPlaneIndex + 31] = y0;  mainVertices[iPlaneIndex + 32] = z0;  mainVertices[iPlaneIndex + 33] = uvx0; mainVertices[iPlaneIndex + 34] = uvy1; mainVertices[iPlaneIndex + 35] = vvtype;

}
// -----------------------------------------------------
// -----------------------------------------------------
GoshaRayIntersectionPlaneManager::GoshaRayIntersectionPlaneManager() {
    iNumberPlanesCreated = 0;
    iPlaneSelected = 0;
    iPlanesStartIndex = 0;
}
GoshaRayIntersectionPlaneManager::~GoshaRayIntersectionPlaneManager() {}
void GoshaRayIntersectionPlaneManager::CreatePlanes(int iX, int iY)
{

    // Dynamically allocate a 2D array of pointers to GoshaRayIntersectionPlane objects
    GoshaRayIntersectionPlane** m_planes = new GoshaRayIntersectionPlane * [iX];
    for (int i = 0; i < iX; ++i) {
        m_planes[i] = new GoshaRayIntersectionPlane[iY];
    }
    iPlanesStartIndex = mainVertices.size();
    // Now, populate the grid with planes
    for (int i = 0; i < iX; i++)
    {
        // Corrected inner loop to iterate through iY
        for (int j = 0; j < iY; j++)
        {
            m_planes[i][j].CreatePlane(i, j);
            iNumberPlanesCreated++;
            m_intersection_planes.push_back(&m_planes[i][j]);

        }
    }

    // Don't forget to free the memory when you're done with the grid to prevent memory leaks!
    // Example cleanup:
    // for (int i = 0; i < iX; ++i) {
    //     delete[] m_planes[i];
    // }
    // delete[] m_planes;
}

GoshaRayIntersectionPlaneManager* g_pGoshaRayIntersectionPlaneManager = NULL;

// -----------------------------------------------------





// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------

GoshaRayIntersectionCube::GoshaRayIntersectionCube()
{

}
GoshaRayIntersectionCube::~GoshaRayIntersectionCube()
{

}

int GoshaRayIntersectionCube::CreatePlane(int CellIDx, int CellIDy) {
    return 0;
}
void GoshaRayIntersectionCube::UpdatePlane() {

}

// -----------------------------------------------------

GoshaRayIntersectionCubeMesh::GoshaRayIntersectionCubeMesh()
{

}
GoshaRayIntersectionCubeMesh::~GoshaRayIntersectionCubeMesh()
{

}

int GoshaRayIntersectionCubeMesh::CreatePlane(int CellIDx, int CellIDy) {

    return 0;

}
void GoshaRayIntersectionCubeMesh::UpdatePlane() {



}
// -----------------------------------------------------

GoshaRayIntersectionMesh::GoshaRayIntersectionMesh()
{


}

GoshaRayIntersectionMesh::~GoshaRayIntersectionMesh()
{



}
int GoshaRayIntersectionMesh::CreatePlane(int CellIDx, int CellIDy) {


    return 0;
}
void GoshaRayIntersectionMesh::UpdatePlane() {



}

// -----------------------------------------------------

PlaneDecals::PlaneDecals()
{

}

PlaneDecals::~PlaneDecals()
{


}
// -----------------------------------------------------

SegmentGoshaRayIntersectionPlane::SegmentGoshaRayIntersectionPlane()
{


}

SegmentGoshaRayIntersectionPlane::~SegmentGoshaRayIntersectionPlane()
{


}



