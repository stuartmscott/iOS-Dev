//
//  Converter.cpp
//  Mechanistic
//
//  Created by Kostadin on 21/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Converter.h"
#include "OBJFileLoader.h"

Converter::Converter(string directory)
{
    gear = new MeshNode();
    loadMesh(directory+"/Gear.obj", gear, false);
    tile = new MeshNode();
    loadMesh(directory+"/Tile.obj", tile, false);
}

Converter::~Converter()
{
    delete gear;
    delete tile;
}

SceneGraphNode* Converter::convert(Model *m)
{
    SceneGraphNode* root = new SceneGraphNode();
    return root;
}