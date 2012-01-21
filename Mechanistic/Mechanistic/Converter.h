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

class Converter
{
private:
    MeshNode* gear;
    MeshNode* tile;
    SceneGraphNode* makeTile(bool withGear);
public:
    Converter(string &directory);
    ~Converter();
    SceneGraphNode* convert(Model* m);
};