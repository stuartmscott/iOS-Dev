//
//  Triangle.h
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#define SMOOTH_NORMALS_ENABLED true
#define TRIANGLE_INDEX_COUNT 3
#define INDEX_BYTE_SIZE 4

struct Triangle
{
    GLint	vertexIndices[TRIANGLE_INDEX_COUNT];	
    GLfloat normal[VERTEX_COORD_COUNT];
    GLint   texCoordIndices[TRIANGLE_INDEX_COUNT];
    GLshort normalIndices[TRIANGLE_INDEX_COUNT];
};