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
    freeBuffers();
    delete material;
}

MeshNode::MeshNode()
{
    textured = false;
    material = new Material();
    setTexEnvMode(MODULATE);
    setCompiled(false);
}

void MeshNode::freeBuffers()
{
    if (compiled)
    {
        free(vertexBuffer);
        free(normalBuffer);
        free(texCoordBuffer);
        free(triangleBuffer);
    }
}

bool MeshNode::isCompiled()
{
    return compiled;
}

void MeshNode::setCompiled(bool value)
{
    if (compiled&&!value)
    {
        freeBuffers();
    }
    this->compiled = value;
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
            GLshort *vIndices = triangles.at(i)->vertexIndices;
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
    
    compiled = false;
} 

void MeshNode::doBeforeRender()
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess);
}

void MeshNode::compile()
{
    if (SMOOTH_NORMALS_ENABLED)
    {
        int totalCoordCount = vertices.size() * VERTEX_COORD_COUNT;
        vertexBuffer = (GLfloat*)malloc(totalCoordCount * VERTEX_BYTE_SIZE);
        normalBuffer = (GLfloat*)malloc(totalCoordCount * VERTEX_BYTE_SIZE);
        int arrayPos = -1;
        for (int i = 0; i<vertices.size(); i++)
        {
            GLfloat *xyzCoords = vertices.at(i)->xyzCoords;
            GLfloat *nCoords = vertices.at(i)->normal;
            for (int j=0; i<VERTEX_COORD_COUNT; j++)
            {
                arrayPos++;
                vertexBuffer[arrayPos] = xyzCoords[j];
                normalBuffer[arrayPos] = nCoords[j];
            }
        }
        
        int totalIndexCount = triangles.size() * TRIANGLE_INDEX_COUNT;
        triangleBuffer = (GLshort*)malloc(totalIndexCount * INDEX_BYTE_SIZE);
        //int vertexIndices[totalIndexCount;
        int totalTexCoordCount = 0;
        if (textured)
        {
            totalTexCoordCount = totalIndexCount * TEXTURE_COORD_COUNT;
            texCoordBuffer = (GLfloat*)malloc(totalTexCoordCount * TEXTURE_COORD_BYTE_SIZE);
        }
        else
        {
            texCoordBuffer = NULL;
        }
        arrayPos = -1;
        int texArrayPos = -1;
        for (int i=0; i<triangles.size(); i++)
        {
            GLshort * vIndices = triangles.at(i)->vertexIndices;
            GLshort * tIndices = (textured) ? triangles.at(i)->texCoordIndices : NULL;
            
            for (int j=0; j<TRIANGLE_INDEX_COUNT; j++)
            {
                arrayPos++;
                triangleBuffer[arrayPos] = vIndices[j];
                if (textured)
                {
                    texArrayPos = vIndices[j] * TEXTURE_COORD_COUNT;
                    GLfloat * uv = textureCoords.at(tIndices[j]);
                    for (int m=0; m<TEXTURE_COORD_COUNT; m++)
                    {
                        texCoordBuffer[texArrayPos + m] = uv[m];
                    }
                }
            }
        }
        
    }
    else
    {
        int totalIndicesCount = triangles.size() * TRIANGLE_INDEX_COUNT;
        vertexBuffer = (GLfloat*)malloc(totalIndicesCount*VERTEX_COORD_COUNT*VERTEX_BYTE_SIZE);
        normalBuffer = (GLfloat*)malloc(totalIndicesCount*VERTEX_COORD_COUNT*VERTEX_BYTE_SIZE);
        int totalTexCoordCount = 0;
        if (textured)
        {
            totalTexCoordCount = totalIndicesCount*TEXTURE_COORD_COUNT;
            texCoordBuffer = (GLfloat*)malloc(totalTexCoordCount * TEXTURE_COORD_BYTE_SIZE);
        }
        triangleBuffer = (GLshort*)malloc(totalIndicesCount*INDEX_BYTE_SIZE);
        int vPos = -1;
        int nPos = -1;
        int tPos = -1;
        int iPos = -1;
        for (int i=0; i<triangles.size(); i++)
        {
            Triangle* triangle = triangles.at(i);
            GLshort* vIndices = triangle->vertexIndices;
            GLshort* nIndices = triangle->normalIndices;
            GLshort* tIndices = (textured) ? triangle->texCoordIndices : NULL;
            for (int j=0; j<TRIANGLE_INDEX_COUNT; j++)
            {
                GLfloat * vCoords = vertices.at(vIndices[j])->xyzCoords;
                GLfloat * nCoords = normals.at(nIndices[j]);
                GLfloat * tCoords = (textured) ? textureCoords.at(tIndices[j]) : NULL;
                for (short k=0; k<VERTEX_COORD_COUNT; k++)
                {
                    vPos++;
                    vertexBuffer[vPos] = vCoords[k];
                    nPos++;
                    normalBuffer[nPos] = nCoords[k];
                }
                if (textured)
                {
                    for (short k=0; k<TEXTURE_COORD_COUNT; k++)
                    {
                        tPos++;
                        texCoordBuffer[tPos] = tCoords[k];
                    }
                }
                iPos++;
                triangleBuffer[iPos] = iPos;
            }
        }
    }
    compiled = true;
}

void MeshNode::drawGeometry()
{
    glVertexPointer(VERTEX_COORD_COUNT, GL_FLOAT, 0, vertexBuffer);
    glNormalPointer(GL_FLOAT, 0, normalBuffer);
    if (textured)
    {
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, valTexEnvMode);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(TEXTURE_COORD_COUNT, GL_FLOAT, 0, texCoordBuffer);
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }
    glDrawElements(GL_TRIANGLES, triangles.size()*TRIANGLE_INDEX_COUNT, GL_UNSIGNED_SHORT, triangleBuffer);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    if (textured)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

void MeshNode::setTextured(bool value)
{
    textured = value;
    compiled = false;
}
