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
    spawnRotation = 0.0f;
    //Top face
    Face *top = loadFace(level, position, 0, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    
    //Side faces
    Face *sf1 = loadFace(level, position, 1, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    Face *sf2 = loadFace(level, position, 2, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    sf2->nInverted = true;
    sf2->eInverted = true;
    Face *sf3 = loadFace(level, position, 3, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    Face *sf4 = loadFace(level, position, 4, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    sf4->sInverted = true;
    sf4->wInverted = true;
    
    //Bottom face
    Face *bot = loadFace(level, position, 5, spawnTileFace, spawnTileIndex, targetTileFace, targetTileIndex);
    
    //Top edges
    Edge *e0 = loadEdge(level, position);
    Edge *e1 = loadEdge(level, position);
    Edge *e2 = loadEdge(level, position);
    Edge *e3 = loadEdge(level, position);
    
    //Side edges
    Edge *e4 = loadEdge(level, position);
    Edge *e5 = loadEdge(level, position);
    Edge *e6 = loadEdge(level, position);
    Edge *e7 = loadEdge(level, position);
    
    //Bottom edges
    Edge *e8 = loadEdge(level, position);
    Edge *e9 = loadEdge(level, position);
    Edge *e10 = loadEdge(level, position);
    Edge *e11 = loadEdge(level, position);
    
    top->setEdges(e2, e1, e0, e3);
    
    e0->setFaces(top, sf1);
    e1->setFaces(top, sf2);
    e2->setFaces(top, sf3);
    e3->setFaces(top, sf4);
    
    sf1->setEdges(e0, e4, e8, e7);
    sf2->setEdges(e1, e5, e9, e4);
    sf3->setEdges(e10, e5, e2, e6);
    sf4->setEdges(e3, e7, e11, e6);
    
    e4->setFaces(sf1, sf2);
    e5->setFaces(sf2, sf3);
    e6->setFaces(sf3, sf4);
    e7->setFaces(sf4, sf1);
    
    e8->setFaces(sf1, bot);
    e9->setFaces(sf2, bot);
    e10->setFaces(sf3, bot);
    e11->setFaces(sf4, bot);
    
    bot->setEdges(e8, e9, e10, e11);
    
    faces[0] = top;
    faces[1] = sf1;
    faces[2] = sf2;
    faces[3] = sf3;
    faces[4] = sf4;
    faces[5] = bot;
    
    edges[0] = e0;
    edges[1] = e1;
    edges[2] = e2;
    edges[3] = e3;
    edges[4] = e4;
    edges[5] = e5;
    edges[6] = e6;
    edges[7] = e7;
    edges[8] = e8;
    edges[9] = e9;
    edges[10] = e10;
    edges[11] = e11;
    
    radius = 2.0f;//8.0
    theta = -1.5f;//-0.7
    phi = 0.5f;//0.5
    destTheta = -M_PI_2;
    destPhi = M_PI_2;
    isSnapping = true;
    gameWon = false;
    numMoves = 0;
    startTime = time(NULL);
    endTime = 0;
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