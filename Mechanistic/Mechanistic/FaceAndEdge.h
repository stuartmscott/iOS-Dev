//
//  Edge.h
//  Mechanistic
//
//  Created by Kostadin on 19/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "Tile.h"
#define NEIGHBOUR_DIFFERENCE 22.5f
#define TILES_PER_FACE 9
#define TILES_PER_EDGE 3

class Face;

class Edge
{
public:
    Face* face1;
    Face* face2;
    Tile* tiles[3];
    Edge(Tile** newTiles);
    ~Edge();
    void setFaces(Face* f1, Face* f2);
    void setSpinning(Face* sender, int tileIndex, float rotation);
};

class Face
{
public:
    bool inverted;
    int freeTileIndex;
    Edge* north;
    Edge* south;
    Edge* west;
    Edge* east;
    Tile* tiles[9];
    Face(Tile** newTiles, int freeTileIndex);
    ~Face();
    void setEdges(Edge* n, Edge* e, Edge* s, Edge* w);
    void setSpinning(Edge* src, int srcIndex, float rotation);
    void setTileSpinning(int tileIndex, float rotation);
    void moveTile(int tileIndex);
    bool isNextToFree(int tileIndex);
};
