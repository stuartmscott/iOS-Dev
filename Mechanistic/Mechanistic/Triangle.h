//
//  Triangle.h
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#define SMOOTH_NORMALS_ENABLED false
#define TRIANGLE_INDEX_COUNT 3
#define INDEX_BYTE_SIZE 8

struct Triangle
{
    GLshort vertexIndices[TRIANGLE_INDEX_COUNT];	
    GLfloat normal[VERTEX_COORD_COUNT];
    GLshort texCoordIndices[TRIANGLE_INDEX_COUNT];
    GLshort normalIndices[TRIANGLE_INDEX_COUNT];
};