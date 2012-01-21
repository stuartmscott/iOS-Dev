//
//  TransformNode.cpp
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "TransformNode.h"
#include <OpenGLES/ES1/gl.h>
#include <vector>

void TransformNode::doBeforeRender()
{
    glPushMatrix();
    for (int i = 0; i < transforms.size(); i++ )
    {
        transforms.at(i)->execute();
    }
}


void TransformNode::doAfterRender()
{
    glPopMatrix();
}

TransformNode::TransformNode(vector<Transform*>& trans)
{
    transforms.clear();
    for(int i=0; i<trans.size(); i++)
    {
        transforms.push_back(trans.at(i));
    }
}

TransformNode::TransformNode(Transform* trans1)
{
    transforms.clear();
    transforms.push_back(trans1);
}

TransformNode::TransformNode(Transform* trans1, Transform* trans2)
{
    transforms.clear();
    transforms.push_back(trans1);
    transforms.push_back(trans2);
}

TransformNode::TransformNode(Transform* trans1, Transform* trans2, Transform* trans3)
{
    transforms.clear();
    transforms.push_back(trans1);
    transforms.push_back(trans2);
    transforms.push_back(trans3);
}

TransformNode::TransformNode(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3)
{
    transforms.clear();
    Transform* trans = new Transform(transType, param1, param2, param3);
    transforms.push_back(trans);
}

TransformNode::TransformNode(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3, GLfloat param4)
{
    transforms.clear();
    Transform* trans = new Transform(transType, param1, param2, param3, param4);
    transforms.push_back(trans);
}
