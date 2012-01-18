//
//  Triangle.cpp
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Vertex.h"
#include "Triangle.h"
#import <OpenGLES/ES1/gl.h>

struct Triangle
{
    GLint	vertexIndices[TRIANGLE_INDEX_COUNT];	
    GLfloat normal[VERTEX_COORD_COUNT];
    GLint   texCoordIndices[TRIANGLE_INDEX_COUNT];
    GLshort normalIndices[TRIANGLE_INDEX_COUNT];
};