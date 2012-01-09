//
//  Triangle.cpp
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Vertex.h"
#include <math.h>

struct Vertex
{
    float xyzCoords[VERTEX_COORD_COUNT];
    float normal[VERTEX_COORD_COUNT];
};

void normaliseNormal(Vertex& v)
{
    float magnitude = (float)sqrt(v.normal[0] * v.normal[0] + v.normal[1] * v.normal[1] + v.normal[2] * v.normal[2]);
    if (magnitude != 0.0f)
    {
        v.normal[0] /= magnitude;
        v.normal[1] /= magnitude;
        v.normal[2] /= magnitude;
    }
}