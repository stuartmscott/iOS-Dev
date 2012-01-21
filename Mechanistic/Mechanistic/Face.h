//
//  Face.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "Tile.h"

class Edge;

class Face
{
public:
    int freeTileIndex;
    Edge* north;
    Edge* south;
    Edge* west;
    Edge* east;
    Tile* tiles[9];
    Face(Tile** newTiles, int freeTileIndex);
    ~Face();
    void setEdges(Edge* n, Edge* e, Edge* s, Edge* w);
};
