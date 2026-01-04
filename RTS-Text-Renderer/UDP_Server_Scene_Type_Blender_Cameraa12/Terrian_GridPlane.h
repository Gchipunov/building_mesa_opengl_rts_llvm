#ifndef TERRIAN_GRIDPLANE_TILEMAP_H
#define TERRIAN_GRIDPLANE_TILEMAP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#ifdef WIN32
#pragma once
#endif



// https://creativemisconfiguration.wordpress.com/category/simcity-2000/#:~:text=Next%20I%20filled%20in%20the,square%205%C3%975%20grid.


class TiledTerrian
{
public:



};


// Tile.h

#ifndef TILE_H
#define TILE_H

#include <glm/glm.hpp>

#

enum class TileType {
    LAND,
    WATER,
    TUNNEL,
    // Add other types as needed
};

class Tile {
public:
    Tile(int x, int y, float height, TileType type = TileType::LAND)
        : x(x), y(y), height(height), type(type) {
    }

    int getX() const { return x; }
    int getY() const { return y; }
    float getHeight() const { return height; }
    TileType getType() const { return type; }
    void setHeight(float newHeight) { height = newHeight; }
    void setType(TileType newType) { type = newType; }

private:
    int x;
    int y;
    float height;
    TileType type;
};

#endif



// Terrain.h

#ifndef TERRAIN_H
#define TERRAIN_H

//#include "Tile.h"
#include <vector>
#include <glm/glm.hpp>

class Terrain {
public:
    Terrain(int width, int height);
    ~Terrain();

    void generateMesh();
    Tile& getTile(int x, int y);
    const std::vector<glm::vec3>& getVertices() const { return vertices; }
    const std::vector<unsigned int>& getIndices() const { return indices; }

    void updateTileHeight(int x, int y, float newHeight);
    void updateTileType(int x, int y, TileType newType);

private:
    int width;
    int height;
    std::vector<std::vector<Tile>> tiles;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    void generateVertices();
    void generateIndices();
};





#endif



class GoshaRayIntersectionPlane
{
public:
    GoshaRayIntersectionPlane();
    ~GoshaRayIntersectionPlane();

    float x0;
    float x1;

    float y0;
    float y1;

    float z0;
    float z1;
    float z2;
    float z3;

    float uvx0;
    float uvx1;

    float uvy0;
    float uvy1;

    int iCellIDX;
    int iCellIDY;

    //float widthX;
   // float widthY;
   // float height;
    int iPlaneIndex;
    int CreatePlane(int CellIDx, int CellIDy);
    void UpdatePlane();
    float vvtype;   // TextureID

    //float 

private:
    // Pointers for the final atlas image data.
    unsigned char* atlasData = nullptr;
    int atlasWidth = 0;
    int atlasHeight = 0;
    int channels = 0; // Number of color channels (e.g., 4 for RGBA).
};




class GoshaRayIntersectionPlaneManager
{
public:
    GoshaRayIntersectionPlaneManager();
    ~GoshaRayIntersectionPlaneManager();
    void CreatePlanes(int iX, int iY);
    int iNumberPlanesCreated;
    int iPlaneSelected;
    int iPlanesStartIndex;
    std::vector< GoshaRayIntersectionPlane*> m_intersection_planes;


};

extern GoshaRayIntersectionPlaneManager* g_pGoshaRayIntersectionPlaneManager;


class GoshaRayIntersectionCube
{
public:
    GoshaRayIntersectionCube();
    ~GoshaRayIntersectionCube();

    float x0;
    float x1;

    float y0;
    float y1;



    int iCellIDX;
    int iCellIDY;

    float widthX;
    float widthY;
    float height;
    int CreatePlane(int CellIDx, int CellIDy);
    void UpdatePlane();

    //float 

private:
    // Pointers for the final atlas image data.
    unsigned char* atlasData = nullptr;
    int atlasWidth = 0;
    int atlasHeight = 0;
    int channels = 0; // Number of color channels (e.g., 4 for RGBA).
};


class GoshaRayIntersectionCubeMesh
{
public:
    GoshaRayIntersectionCubeMesh();
    ~GoshaRayIntersectionCubeMesh();

    float x0;
    float x1;

    float y0;
    float y1;

    int iCellIDX;
    int iCellIDY;

    float widthX;
    float widthY;
    float height;

    glm::vec4 Positions[8];
    int CreatePlane(int CellIDx, int CellIDy);
    void UpdatePlane();

    //float 

private:
    // Pointers for the final atlas image data.
    unsigned char* atlasData = nullptr;
    int atlasWidth = 0;
    int atlasHeight = 0;
    int channels = 0; // Number of color channels (e.g., 4 for RGBA).
};




class GoshaRayIntersectionMesh
{
public:
    GoshaRayIntersectionMesh();
    ~GoshaRayIntersectionMesh();

    float x0;
    float x1;

    float y0;
    float y1;

    int iCellIDX;
    int iCellIDY;

    float widthX;
    float widthY;
    float height;

    glm::vec4 Positions[36];
    int CreatePlane(int CellIDx, int CellIDy);
    void UpdatePlane();

    //float 

private:
    // Pointers for the final atlas image data.
    unsigned char* atlasData = nullptr;
    int atlasWidth = 0;
    int atlasHeight = 0;
    int channels = 0; // Number of color channels (e.g., 4 for RGBA).
};

class PlaneDecals
{
public:
    PlaneDecals();
    ~PlaneDecals();


    glm::vec4 UVs; // x x0 y y0, z x1 , w y1
    glm::vec2 UVPositionCenter; // x , y

};
class SegmentGoshaRayIntersectionPlane
{
public:
    SegmentGoshaRayIntersectionPlane();
    ~SegmentGoshaRayIntersectionPlane();

    int iSubDivides;

    std::vector<GoshaRayIntersectionPlane> sub_planes;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
};

#endif
