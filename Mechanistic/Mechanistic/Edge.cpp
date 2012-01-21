//
//  Edge.cpp
//  Mechanistic
//
//  Created by Kostadin on 19/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "FaceAndEdge.h"

Edge::Edge(Tile** newTiles)
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

void Edge::setFaces(Face* f1, Face* f2)
{
    face1 = f1;
    face2 = f2;
}

void Edge::setSpinning(Face* sender, int tileIndex){
    Tile* t = tiles[tileIndex];
    if (t->hasGear){
        if(!t->gear->isSpinning){
            t->gear->isSpinning = true;
            if (sender==face1)
                face2->setSpinning(this, tileIndex);
            else
                face1->setSpinning(this, tileIndex);
        }
    }
}