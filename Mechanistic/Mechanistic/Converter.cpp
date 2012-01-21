//
//  Converter.cpp
//  Mechanistic
//
//  Created by Kostadin on 21/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Converter.h"
#include "OBJFileLoader.h"
#include "TransformNode.h"
#include "LightNode.h"

Converter::Converter(string directory)
{
    gear = new MeshNode();
    loadMesh(directory+"/Gear.obj", gear, false);
    gear->material->setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
    tile = new MeshNode();
    loadMesh(directory+"/Tile.obj", tile, false);
    tile->material->setAmbient(0.84f, 0.65f, 0.43f, 1.0f);
}

Converter::~Converter()
{
    delete gear;
    delete tile;
}

SceneGraphNode* Converter::convert(Model *m)
{
    SceneGraphNode* root = new SceneGraphNode();
    TransformNode* scaleEverything = new TransformNode(SCALE, 0.1f, 0.1f, 0.1f);
    Transform* rotate = new Transform(ROTATE, 0.0f, 0.0f, 0.0f, 1.0f);
    Transform* translate = new Transform(TRANSLATE, 0.0f, -3.2f, 0.0f);
    TransformNode* positionTile = new TransformNode(rotate, translate);
    positionTile->getChildren()->push_back(tile);
    scaleEverything->getChildren()->push_back(gear);
    scaleEverything->getChildren()->push_back(positionTile);
    root->getChildren()->push_back(scaleEverything);
    return root;
}