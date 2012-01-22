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

Converter::Converter(string &directory)
{
    gear = new MeshNode();
    string gfn = directory+"/Gear.obj";
    loadMesh(gfn, gear, false);
    gear->material->setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
    tile = new MeshNode();
    string tfn = directory+"/Tile.obj";
    loadMesh(tfn, tile, false);
    tile->material->setAmbient(0.84f, 0.65f, 0.43f, 1.0f);
}

Converter::~Converter()
{
    delete gear;
    delete tile;
}

SceneGraphNode* Converter::makeTile(Tile* tileRef)
{
    SceneGraphNode* tileGroup = new SceneGraphNode();
    if (!tileRef->empty)
    {
        if (tileRef->hasGear)
        {
            Transform* rotate = new Transform(ROTATE, tileRef->gear->rotation, 0.0f, 0.0f, 1.0f);
            Transform* translate = new Transform(TRANSLATE, 0.0f, 3.2f, 0.0f);
            TransformNode* positionGear = new TransformNode(rotate, translate);
            positionGear->getChildren()->push_back(gear);
            tileGroup->getChildren()->push_back(positionGear);
        }
        tileGroup->getChildren()->push_back(tile);
    }
    return tileGroup;
}

SceneGraphNode* Converter::makeFace(Face* faceRef)
{
    SceneGraphNode* faceGroup = new SceneGraphNode();
    for(int i=0; i<9; i++)
    {
        SceneGraphNode* tileGroup = makeTile(faceRef->tiles[i]);
        TransformNode* positionTileGroup = new TransformNode(TRANSLATE, ((i%3)-1.0f)*20.0f, 0.0f, ((i/3)-1.0f)*20.0f);
        positionTileGroup->getChildren()->push_back(tileGroup);
        faceGroup->getChildren()->push_back(positionTileGroup);
    }
    return faceGroup;
}

SceneGraphNode* Converter::convert(Model *m)
{
    SceneGraphNode* root = new SceneGraphNode();
    TransformNode* scaleEverything = new TransformNode(SCALE, 0.1f, 0.1f, 0.1f);
    //scaleEverything->getChildren()->push_back(makeTile(m->faces[0]->tiles[0]));
    scaleEverything->getChildren()->push_back(makeFace(m->faces[0]));
    root->getChildren()->push_back(scaleEverything);
    return root;
}