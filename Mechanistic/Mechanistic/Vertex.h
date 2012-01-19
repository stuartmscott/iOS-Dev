//
//  Triangle.h
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#import <OpenGLES/ES1/gl.h>
#define VERTEX_BYTE_SIZE 4
#define VERTEX_COORD_COUNT 3

struct Vertex
{
    GLfloat xyzCoords[VERTEX_COORD_COUNT];
    GLfloat normal[VERTEX_COORD_COUNT];
};

void normaliseNormal(Vertex& v);