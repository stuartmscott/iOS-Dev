//
//  MeshNode.h
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "SceneGraphNode.h"
#include "Vertex.h"
#include "Triangle.h"
#include <OpenGLES/ES2/gl.h>
#include <vector>

#define TEXTURE_COORD_COUNT 2
#define TEXTURE_COORD_BYTE_SIZE 4

using namespace std;

class MeshNode: SceneGraphNode
{
private:
    bool    compiled;
    bool    textured;
    bool    textureID;
    vector<Vertex*> vertices;
    vector<GLfloat[3]>  normals;
    vector<Triangle*>   triangles;
    vector<GLfloat[2]>  textureCoords;
    GLfloat* vertexBuffer;
    GLfloat* normalBuffer;
    GLfloat* texCoordBuffer;
    GLint*   triangleBuffer;
public:
    MeshNode();
    ~MeshNode();
    bool isCompiled();
    void setCompiled(bool value);
};