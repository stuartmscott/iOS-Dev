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

class TransformNode:public SceneGraphNode
{
public:
    vector<Transform*> transforms;
    TransformNode(vector<Transform*>& trans);
    TransformNode(Transform* trans1);
    TransformNode(Transform* trans1, Transform* trans2);
    TransformNode(Transform* trans1, Transform* trans2, Transform* trans3);
    TransformNode(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3);
    TransformNode(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3, GLfloat param4);
    ~TransformNode();
    void doBeforeRender();
    void doAfterRender();
};