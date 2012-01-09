//
//  Triangle.cpp
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Vertex.h"
#include "Triangle.h"

struct Triangle
{
    int	vertexIndices[TRIANGLE_INDEX_COUNT];	
    float normal[VERTEX_COORD_COUNT];
    int texCoordIndices[TRIANGLE_INDEX_COUNT];
    short normalIndices[TRIANGLE_INDEX_COUNT];
};