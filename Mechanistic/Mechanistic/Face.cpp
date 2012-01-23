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
    
    nInverted = eInverted = sInverted = wInverted = false;
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
        if (nInverted)
            //0 1 2 = 8 5 2
            srcIndex = 2-srcIndex;
        //0 1 2 = 0 1 2
        tileIndex = srcIndex;
    } else if (src==east) {
        if (eInverted)
            //0 1 2 = 8 5 2
            srcIndex = 2-srcIndex;
        //0 1 2 = 2 5 8
        tileIndex = (srcIndex*3)+2;
    } else if (src==south) {
        if (sInverted)
            //0 1 2 = 8 5 2
            srcIndex = 2-srcIndex;
        //0 1 2 = 6 7 8
        tileIndex = 6+srcIndex;
    } else {
        if (wInverted)
            //0 1 2 = 6 3 0
            srcIndex = 2-srcIndex;
        //0 1 2 = 0 3 6
        tileIndex = (srcIndex*3);
    }
    setTileSpinning(tileIndex, -rotation);
}

void Face::setTileSpinning(int tileIndex, float rotation) {
    Tile* t = tiles[tileIndex];
    if (t->hasGear){
        if(!t->gear->isSpinning){
            t->gear->isSpinning = true;
            t->gear->rotation = rotation;
            float newRotation = -(rotation + NEIGHBOUR_DIFFERENCE);
            //Make neighours spin
            //Above
            int newIndex = tileIndex-3;
            if(newIndex<0){
                int tInd = tileIndex;
                if(nInverted)
                    tInd = 2-tInd;
                north->setSpinning(this, tInd, newRotation);
            }else
                setTileSpinning(newIndex, newRotation);
            //Below
            newIndex = tileIndex+3;
            if(newIndex>=9){
                int tInd = tileIndex-6;
                if(sInverted)
                    tInd = 2-tInd;
                south->setSpinning(this, tInd, newRotation);
            } else
                setTileSpinning(newIndex, newRotation);
            //Left
            if (tileIndex%3==0) {
                int tInd = tileIndex/3;
                if(wInverted)
                    tInd = 2-tInd;
                west->setSpinning(this, tInd, newRotation);
            } else {
                setTileSpinning(tileIndex-1, newRotation);
            }
            //Right
            if (tileIndex%3==2) {
                int tInd = (tileIndex-2)/3;
                if(eInverted)
                    tInd = 2-tInd;
                east->setSpinning(this, tInd, newRotation);
            } else {
                setTileSpinning(tileIndex+1, newRotation);
            }
        }
    }
}

bool Face::isNextToFree(int tileIndex) {
    int n, e, s, w;
    n = e = s = w = -1;
    if (tileIndex>2)
        n = tileIndex-3;
    if ((tileIndex%3)<2)
        e = tileIndex+1;
    if (tileIndex<6)
        s = tileIndex+3;
    if ((tileIndex%3)>0)
        e = tileIndex-1;
    
    int f = freeTileIndex;
    return (n==f||e==f||s==f||w==f);
}

void Face::moveTile(int tileIndex) {
    Tile* temp = tiles[tileIndex];
    tiles[tileIndex] = tiles[freeTileIndex];
    tiles[freeTileIndex] = temp;
    freeTileIndex = tileIndex;
}