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
        transforms.at(i).execute();
    }
}


void TransformNode::doAfterRender()
{
    glPopMatrix();
}

TransformNode::TransformNode(vector<Transform> trans)
{
    transforms = trans;
}