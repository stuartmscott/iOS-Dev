//
//  Edge.cpp
//  Mechanistic
//
//  Created by Kostadin on 19/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Edge.h"

Edge::Edge(Tile** &newTiles)
{
    for (int i=0; i<3; i++)
    {
        tiles[i] = newTiles[i];
    }
}

Edge::~Edge()
{
    delete tiles[0];
    delete tiles[1];
    delete tiles[2];
}

void setFaces(Face* n, Face* s)
{
    north = n;
    south = s;
}