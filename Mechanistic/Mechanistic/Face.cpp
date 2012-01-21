//
//  Face.cpp
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Face.h"

Face::Face(Tile** newTiles)
{
    for (int i=0; i<9; i++)
    {
        tiles[i] = newTiles[i];
    }
}

Face::~Face()
{
    for (int i=0; i<9; i++)
    {
        delete tiles[i];
    }
}

void Face::setEdges(Edge* n, Edge* e, Edge* s, Edge* w)
{
    north = n;
    east = e;
    south = s;
    west = w;
}