//
//  SceneGraphNode.cpp
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "SceneGraphNode.h"

SceneGraphNode::SceneGraphNode()
{
}

SceneGraphNode::~SceneGraphNode()
{
    children.clear();
}

void SceneGraphNode::setCompiled(bool value)
{
    this->compiled = value;
}

vector<SceneGraphNode*>* SceneGraphNode::getChildren()
{
    return &children;
}

void SceneGraphNode::setChildren(vector<SceneGraphNode *> &newChildren)
{
    children = newChildren;
}

void SceneGraphNode::compile()
{
    
}

void SceneGraphNode::doBeforeRender()
{
    
}

void SceneGraphNode::doBeforeRenderChildren()
{
    
}

void SceneGraphNode::doAfterRenderChildren()
{
    
}

void SceneGraphNode::doAfterRender()
{
    
}