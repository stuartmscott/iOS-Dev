//
//  Converter.h
//  Mechanistic
//
//  Created by Kostadin on 21/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "MeshNode.h"
#include <string>
#include "Model.h"
#define TILE_HEIGHT 20.0f
#define TILE_GAP 0.4f
#define TC_TO_TC_ON_FACE 20.4f
#define SCALE_FACTOR 0.02f
#define LIFT_GEAR 3.2f
#define FACE_DISTANCE_FROM_ORIGIN 45.02498f
#define EDGE_DISTANCE_FROM_ORIGIN 53.474935f

class Converter
{
private:
    MeshNode* gear;
    MeshNode* edgeTile;
    MeshNode* faceTile;
    SceneGraphNode* makeTile(Tile* tileRef, bool isEdge);
    SceneGraphNode* makeFace(Face* faceRef);
    SceneGraphNode* makeEdge(Edge* edgeRef);
public:
    Converter(string &directory);
    ~Converter();
    SceneGraphNode* convert(Model* m);
};