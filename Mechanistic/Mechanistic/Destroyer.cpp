//
//  Destroyer.cpp
//  Mechanistic
//
//  Created by Kostadin on 22/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Destroyer.h"
#include "TransformNode.h"
#include "LightNode.h"
#include <stack>
#include <vector>
#include <typeinfo>

using namespace std;

void enlist(SceneGraphNode* victim, vector<SceneGraphNode*> &victims, bool deleteMeshes)
{
    if ((!victim->visitedByDeath)&&(deleteMeshes||(typeid(*victim)!=typeid(MeshNode))))
    {
        victims.push_back(victim);
        victim->visitedByDeath = true;
    }
}

void annihilate(SceneGraphNode* root, bool deleteMeshes)
{
    vector<SceneGraphNode*> victims;
    stack<SceneGraphNode*> nodeStack;
    stack<int> counterStack;
    victims.clear();
    nodeStack.push(root);
    counterStack.push(-1);
    enlist(root, victims, deleteMeshes);
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
            nodeStack.push(child);
            counterStack.push(-1);
            enlist(child, victims, deleteMeshes);
        }
        else
        {
            nodeStack.pop();
            counterStack.pop();
        }
    }
    for (int i=0; i<victims.size(); i++)
    {
        SceneGraphNode* victim = victims.at(i);
        if (typeid(*victim)==typeid(TransformNode))
        {
            delete (TransformNode*) victim;
        } 
        else if (typeid(*victim)==typeid(LightNode))  
        {
            delete (LightNode*) victim;
        }
        else if (typeid(*victim)==typeid(MeshNode))  
        {
            delete (MeshNode*) victim;
        }
        else
        {
            delete victim;
        }
        int j = 0+1;
    }
}