//
//  Model.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Model.h"
#include <stdlib.h>
#include <math.h>
#define IS_EMPTY 0
#define IS_TILE 1
#define IS_GEAR 2
#define IS_START 3
#define IS_END 4

Tile** makeTiles(int num, int freeIndex)
{
    Tile** tiles = (Tile**)malloc(sizeof(Tile)*num);
    for (int i=0;i<num;i++){
        tiles[i] = new Tile();
        if (i==freeIndex)
            tiles[i]->empty = true;
    }
    return tiles;
}

Face* loadFace(const int * level, int & position, int currentFaceIndex, int & startFaceIndex, int & startTileIndex, int & endFaceIndex, int & endTileIndex)
{
    int freeTileIndex = 0;
    Tile** tiles = (Tile**)malloc(sizeof(Tile)*TILES_PER_FACE);
    for (int i=0;i<TILES_PER_FACE;i++){
        tiles[i] = new Tile();
        int value = level[position+i];
        if (value==IS_EMPTY)
        {
            freeTileIndex = i;
            tiles[i]->empty = true;
        }
        if (value>=IS_GEAR)
        {
            tiles[i]->setGear(new Gear());
        }
        if (value==IS_START)
        {
            startFaceIndex = currentFaceIndex;
            startTileIndex = i;
            tiles[i]->moveable = false;
        }
        if (value==IS_END)
        {
            endFaceIndex = currentFaceIndex;
            endTileIndex = i;
            tiles[i]->moveable = false;
        }
    }
    position+=TILES_PER_FACE;
    return new Face(tiles, freeTileIndex);
}

Edge* loadEdge(const int * level,  int & position)
{
    Tile** tiles = (Tile**)malloc(sizeof(Tile)*TILES_PER_EDGE);
    for (int i=0;i<TILES_PER_EDGE;i++){
        tiles[i] = new Tile();
        if (level[position+i]==IS_EMPTY)
        {
            tiles[i]->empty = true;
        }
        if (level[position+i]>=IS_GEAR)
        {
            tiles[i]->setGear(new Gear());
        }
    }
    position+=TILES_PER_EDGE;
    return new Edge(tiles);
}

Model::Model(const int * level)
{
    int position = 0;
    //spawnTileFace = sFaceIndex;
    //spawnTileIndex = sTileIndex;
    spawnRotation = 0.0f;
    //targetTileFace = tFaceIndex;
    //targetTileIndex = tTileIndex;
    //Top face
    Face *top = loadFace(level, position, 0, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    
    //Side faces
    Face *sf0 = loadFace(level, position, 1, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    Face *sf1 = loadFace(level, position, 2, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    sf1->northInverted = true;
    Face *sf2 = loadFace(level, position, 3, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    Face *sf3 = loadFace(level, position, 4, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    sf3->southInverted = true;
    //sf3->tiles[4]->setGear(new Gear());
    
    //Bottom face
    Face *bot = loadFace(level, position, 5, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    
    //Top edges
    Edge *te0 = loadEdge(level, position);
    Edge *te1 = loadEdge(level, position);
    Edge *te2 = loadEdge(level, position);
    Edge *te3 = loadEdge(level, position);
    
    
    
    //Side edges
    Edge *se0 = loadEdge(level, position);
    Edge *se1 = loadEdge(level, position);
    Edge *se2 = loadEdge(level, position);
    Edge *se3 = loadEdge(level, position);
    
    //Bottom edges
    Edge *be0 = loadEdge(level, position);
    Edge *be1 = loadEdge(level, position);
    Edge *be2 = loadEdge(level, position);
    Edge *be3 = loadEdge(level, position);
    
    
    
    top->setEdges(te2, te1, te0, te3);
    
    te0->setFaces(top, sf0);
    te1->setFaces(top, sf1);
    te2->setFaces(top, sf2);
    te3->setFaces(top, sf3);
    
    sf0->setEdges(te0, se0, be0, se3);
    sf1->setEdges(te1, se1, be1, se0);
    sf2->setEdges(te2, se2, be2, se1);
    sf3->setEdges(te3, se3, be3, se2);
    
    se0->setFaces(sf1, sf0);
    se1->setFaces(sf2, sf1);
    se2->setFaces(sf3, sf2);
    se3->setFaces(sf0, sf3);
    
    te0->setFaces(sf0, bot);
    te1->setFaces(sf1, bot);
    te2->setFaces(sf2, bot);
    te3->setFaces(sf3, bot);
    
    bot->setEdges(te0, te1, te2, te3);
    
    faces[0] = top;
    faces[1] = sf0;
    faces[2] = sf1;
    faces[3] = sf2;
    faces[4] = sf3;
    faces[5] = bot;
    
    edges[0] = te0;
    edges[1] = te1;
    edges[2] = te2;
    edges[3] = te3;
    edges[4] = se0;
    edges[5] = se1;
    edges[6] = se2;
    edges[7] = se3;
    edges[8] = be0;
    edges[9] = be1;
    edges[10] = be2;
    edges[11] = be3;
    
    //Moved to loadFace()
    //faces[spawnTileFace]->tiles[spawnTileIndex]->moveable = false;
    //faces[targetTileFace]->tiles[targetTileIndex]->moveable = false;
    
    radius = 2.0f;//8.0
    theta = -1.5f;//-0.7
    phi = 0.5f;//0.5
    destTheta = -M_PI_2;
    destPhi = M_PI_2;
    isSnapping = true;
    gameWon = false;
}

Model::~Model()
{
    for (int i =0;i<6;i++)
    {
        delete faces[i];
    }
    for (int i =0;i<12;i++)
    {
        delete edges[i];
    }
}