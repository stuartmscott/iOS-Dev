//
//  SceneGraphNode.h
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <vector>

using namespace std;

class SceneGraphNode
{
private:
    vector<SceneGraphNode*> children;
protected:
    bool compiled;
public:
    SceneGraphNode();
    ~SceneGraphNode();
    vector<SceneGraphNode*>* getChildren();
    void setChildren(vector<SceneGraphNode*>&newChildren);
    virtual void setCompiled(bool comp);
    virtual void compile();
    virtual void doBeforeRender();
    virtual void doBeforeRenderChildren();
    virtual void doAfterRenderChildren();
    virtual void doAfterRender();
};
