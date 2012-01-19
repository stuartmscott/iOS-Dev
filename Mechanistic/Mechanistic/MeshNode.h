//
//  MeshNode.h
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "SceneGraphNode.h"
#include "Vertex.h"
#include "Triangle.h"
#include "Material.h"
#include <OpenGLES/ES1/gl.h>
#include <vector>

#define TEXTURE_COORD_COUNT 2
#define TEXTURE_COORD_BYTE_SIZE 4

using namespace std;

enum TexEnvMode {
    MODULATE, DECAL, BLEND, REPLACE
};

class MeshNode: SceneGraphNode
{
private:
    bool    compiled;
    bool    textured;
    bool    textureID;
    int     valTexEnvMode;
    Material*   material;
    TexEnvMode  texEnvMode;	
    vector<Vertex*> vertices;
    vector<GLfloat*>  normals;
    vector<Triangle*>   triangles;
    vector<GLfloat*>  textureCoords;
    GLfloat* vertexBuffer;
    GLfloat* normalBuffer;
    GLfloat* texCoordBuffer;
    GLshort*   triangleBuffer;
	void freeBuffers();
public:
    MeshNode();
    ~MeshNode();
    bool isCompiled();
    void setCompiled(bool value);
    void setTexEnvMode(TexEnvMode texEnvMode);
    void setVertices(vector<Vertex*> vertices);
    void setNormals(vector<GLfloat*> normals);
    void setTriangles(vector<Triangle*> triangles);
    void setTextureCoords(vector<GLfloat*> textureCoords);
    void calcSmoothNormals();
    void doBeforeRender();
    void compile();
    void drawGeometry();
    void setTextured(bool value);
};