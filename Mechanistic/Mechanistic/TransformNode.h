//
//  TransformNode.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "SceneGraphNode.h"
#include "Transform.h"
#include <vector>

class TransformNode:SceneGraphNode
{
public:
    vector<Transform> transforms;
    TransformNode(vector<Transform> trans);
    ~TransformNode();
    void doBeforeRender();
    void doAfterRender();
};