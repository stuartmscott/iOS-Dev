//
//  SceneGraphNode.h
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#include <vector>

using namespace std;

class SceneGraphNode
{
private:
    bool compiled;
    vector<SceneGraphNode*> children;
public:
    SceneGraphNode();
    ~SceneGraphNode();
    vector<SceneGraphNode*> getChildren();
    void setChildren(vector<SceneGraphNode*> newChildren);
    bool isCompiled;
    void setCompiled(bool comp);
    virtual void compile();
    virtual void doBeforeRender();
    virtual void doBeforeRenderChildren();
    virtual void doAfterRenderChildren();
    virtual void doAfterRender();
};