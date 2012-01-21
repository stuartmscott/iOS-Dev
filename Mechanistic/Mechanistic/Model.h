//
//  Model.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "Face.h"
#include "Edge.h"
#define MOVE_PLAY 5.0f
#define WIDTH 320.0f
#define HEIGHT 480.0f
#define NEAR_CLIP 0.01f
#define FAR_CLIP 100.0f

class Model
{
public:
    int spawnTileFace, spawnTileIndex;
    int targetFace, targetTileIndex;
    float startX, startY, currX, currY;
    float eye[3], up[3];
    float radius, theta, phi;
    bool isDragging;
    Face* faces[6];
    Edge* edges[12];
    Model();
    ~Model();
    void moveTile(int faceIndex, int tileIndex);
};
