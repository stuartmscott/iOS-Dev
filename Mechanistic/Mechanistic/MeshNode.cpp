//
//  MeshNode.cpp
//  Mechanistic
//
//  Created by Kostadin on 09/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "MeshNode.h"
#include "Math.h"

MeshNode::~MeshNode()
{
    free(vertexBuffer);
    free(normalBuffer);
    free(texCoordBuffer);
    free(triangleBuffer);
    delete material;
}

MeshNode::MeshNode()
{
    textured = false;
    material = new Material();
    setTexEnvMode(MODULATE);
    setCompiled(false);
}

bool MeshNode::isCompiled()
{
    return compiled;
}

void MeshNode::setCompiled(bool compiled)
{
    this->compiled = compiled;
}

void MeshNode::setTexEnvMode(TexEnvMode texEnvMode)
{
    switch (texEnvMode) {
        case MODULATE:
            valTexEnvMode = GL_MODULATE;
            break;
        case DECAL:
            valTexEnvMode = GL_DECAL;
            break;
        case BLEND:
            valTexEnvMode = GL_BLEND;
            break;
        case REPLACE:
            valTexEnvMode = GL_REPLACE;
            break;
    }
    this->texEnvMode = texEnvMode;
}

void MeshNode::setVertices(vector<Vertex*> vertices)
{
    this->vertices = vertices;
    setCompiled(false);
}

void MeshNode::setNormals(vector<GLfloat*> normals)
{
    this->normals = normals;
}

void MeshNode::setTriangles(vector<Triangle*> triangles)
{
    this->triangles = triangles;
    setCompiled(false);    
}

void MeshNode::setTextureCoords(vector<GLfloat*> textureCoords)
{
    this->triangles = triangles;
    if (textured)
        setCompiled(false);      
}

//Dr. Steve Maddock and Dr. Michael Meredith
/*
void MeshNode::calcSmoothNormals()
{
    int i, j;
    float mag;
    float nx, ny, nz;
    float avec[3];
    float bvec[3];
    
    for (i=0; i<vertices.size(); i++)
    {
        Vertex* v = vertices.at(i);
        v->normal[0] = 0;
        v->normal[1] = 0;
        v->normal[2] = 0;
    }
    
    for (int i=0; i<triangles.size(); i++)
    {
        for (j=0; j<3; j++)
        {
            GLint *vIndices = triangles.at(i)->vertexIndices;
            avec[j] = vertices.at(vIndices[0])->xyzCoords[j] - vertices.at(vIndices[1])->xyzCoords[j];
            bvec[j] = vertices.at(vIndices[0])->xyzCoords[j] - vertices.at(vIndices[2])->xyzCoords[j];
        }
    }
    // Cross product of avec and bvec to determine the triangle normal
    nx = avec[1] * bvec[2] - avec[2] * bvec[1];
    ny = avec[2] * bvec[0] - avec[0] * bvec[2];
    nz = avec[0] * bvec[1] - avec[1] * bvec[0];
    mag = sqrt(nx * nx + ny * ny + nz * nz);
    if (mag != 0.0f)
    {
        nx /= mag;
        ny /= mag;
        nz /= mag;
        GLfloat *normal = triangles.at(i)->normal;
        normal[0] = nx;
        normal[1] = ny;
        normal[2] = nz;
    }
    
    for (j = 0; j < 3; j++)
    {
        GLfloat * normal = vertices.at(triangles.at(i)->vertexIndices[j])->normal;
        normal[0] += nx;
        normal[1] += ny;
        normal[2] += nz;
    }
} 
*/