//
//  Edge.h
//  Mechanistic
//
//  Created by Kostadin on 19/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "Tile.h"

class Face;

class Edge
{
public:
    Face* north;
    Face* south;
    Tile* tiles[3];
    Edge(Tile** &newTiles);
    ~Edge();
    void setFaces(Face* n, Face* s);
};