//
//  Face.cpp
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "FaceAndEdge.h"

Face::Face(Tile** newTiles, int freeIndex)
{
    freeTileIndex = freeIndex;
    for (int i=0; i<9; i++)
    {
        tiles[i] = newTiles[i];
    }
    delete [] newTiles;
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

void Face::setSpinning(Edge* src, int srcIndex, float rotation) {
    //depending on src's direction (nesw) the actual index will vary
    int tileIndex;
    if (src==north) {
        //0 1 2 = 0 1 2
        tileIndex = srcIndex;
    } else if (src==east) {
        //0 1 2 = 2 5 8
        tileIndex = (srcIndex*3)+2;
    } else if (src==south) {
        //0 1 2 = 6 7 8
        tileIndex = 6+srcIndex;
    } else {
        //0 1 2 = 0 3 6
        tileIndex = (srcIndex*3);
    }
    setTileSpinning(tileIndex, rotation);
}

void Face::setTileSpinning(int tileIndex, float rotation) {
    Tile* t = tiles[tileIndex];
    if (t->hasGear){
        if(!t->gear->isSpinning){
            t->gear->isSpinning = true;
            t->gear->rotation = rotation;
            float newRotation = rotation + NEIGHBOUR_DIFFERENCE;
            //Make neighours spin
            //Above
            int newIndex = tileIndex-3;
            if(newIndex<0)
                north->setSpinning(this, tileIndex, newRotation);
            else
                setTileSpinning(newIndex, newRotation);
            //Below
            newIndex = tileIndex+3;
            if(newIndex>=9)
                south->setSpinning(this, tileIndex-6, newRotation);
            else
                setTileSpinning(newIndex, newRotation);
            //Left
            if (tileIndex%3==0) {
                west->setSpinning(this, tileIndex/3, newRotation);
            } else {
                setTileSpinning(tileIndex-1, newRotation);
            }
            //Right
            if (tileIndex%3==2) {
                west->setSpinning(this, (tileIndex-2)/3, newRotation);
            } else {
                setTileSpinning(tileIndex+1, newRotation);
            }
        }
    }

}