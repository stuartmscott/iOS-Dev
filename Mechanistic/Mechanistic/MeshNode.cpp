//
//  MeshNode.cpp
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "MeshNode.h"

MeshNode::~MeshNode()
{
    free(vertexBuffer);
    free(normalBuffer);
    free(texCoordBuffer);
    free(triangleBuffer);
}