//
//  SceneGraphRenderer.cpp
//  Mechanistic
//
//  Created by Kostadin on 19/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "SceneGraphRenderer.h"
#include "MeshNode.h"
#include "LightNode.h"
#include <stack>
#include <typeinfo>

bool mustExecuteRenderEvents(SceneGraphNode * node, bool lightsMode)
{
    // No need to apply material properties when we deal with lights
    if ((lightsMode) && (typeid(node)==typeid(MeshNode)))
    {
        return false;
    }
    
    // No need to draw lights twice
    if ((!lightsMode) && (typeid(node)==typeid(LightNode)))
    {
        return false;
    }
    return true;
}

void processBeforeRender(stack<SceneGraphNode*>& nodeStack, stack<int>& counterStack, SceneGraphNode * node, bool lightsMode)
{
    nodeStack.push(node);
    counterStack.push(-1);
    bool executeBeforeRender = mustExecuteRenderEvents(node, lightsMode);
    if (executeBeforeRender)
    {
        node->doBeforeRender();
    }
    
    node->compile();
    
    // Geometry must be drawn after all lights are configured so it is
    // properly shaded
    if ((!lightsMode) && (typeid(*node)==typeid(MeshNode)))
    {
        ((MeshNode *) node)->drawGeometry();
    }
    
    if (executeBeforeRender)
    {
        node->doBeforeRenderChildren();
    }
}

void processAfterRender(stack<SceneGraphNode*>& nodeStack, stack<int>& counterStack, SceneGraphNode * node, bool lightsMode)
{
    if (mustExecuteRenderEvents(node, lightsMode))
    {
        node->doAfterRender();
    }
    nodeStack.pop();
    counterStack.pop();
}

void parseGraph(SceneGraphNode * root, bool lightsMode)
{
    // Stacks are used to avoid recursion.
    stack<SceneGraphNode*> nodeStack;
    stack<int> counterStack;
    processBeforeRender(nodeStack, counterStack, root, lightsMode);
    while (nodeStack.size()>0)
    {
        SceneGraphNode * node = nodeStack.top();
        int childIndex = counterStack.top();
        vector<SceneGraphNode*>* children = node->getChildren();
        int childCount = children->size();
        if (childIndex < (childCount - 1))
        {
            childIndex++;
            //counterStack.set(counterStack.size() - 1, childIndex);
            counterStack.pop();
            counterStack.push(childIndex);
            SceneGraphNode * child = node->getChildren()->at(childIndex);
            processBeforeRender(nodeStack, counterStack, child, lightsMode);
        }
        else
        {
            processAfterRender(nodeStack, counterStack, node, lightsMode);
        }
    }
}

void render(SceneGraphNode* root)
{
    if (root == NULL) return;
    parseGraph(root, true);
    parseGraph(root, false);
    // Load the default material
    MeshNode * defaultMaterialNode = new MeshNode();
    defaultMaterialNode->doBeforeRender();
    delete defaultMaterialNode;
}