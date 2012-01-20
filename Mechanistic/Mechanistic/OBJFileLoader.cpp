//
//  OBJFileLoader.cpp
//  Mechanistic
//
//  Created by Kostadin on 20/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "OBJFileLoader.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <OpenGLES/ES1/gl.h>
#include "Vertex.h"

using namespace std;

void tokenize(string text, char* separators, vector<string> &tokens)
{
    char ctext[text.size()];
    text.copy(ctext, text.size());
    char* token = strtok( ctext, separators );
    while( token != NULL )
    {
        tokens.push_back(token);
        token = strtok( NULL, separators );
    }
}

void replaceAll(string& str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void trim(string& str)
{
    string::size_type pos = str.find_last_not_of(' ');
    if(pos != string::npos) {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if(pos != string::npos) str.erase(0, pos);
    }
    else str.erase(str.begin(), str.end());
}

void loadMesh(const string &fileName, MeshNode * destination, bool textured)
{
    vector<Vertex*> vertices;
    vector<GLfloat*> normals;
    vector<Triangle*> triangles;
    vector<GLfloat*> texCoords;
    char delims[] = " ";
    vector<string> tokens;
    string line;
    ifstream in(fileName.c_str());
    string doubleSpace = "  ";
    string space = " ";
    char iDelims[] = "/";
    while (getline(in,line))
    {
        trim(line);
        replaceAll(line, doubleSpace, space);
        tokens.clear();
        tokenize(line, delims, tokens);
        string cmd = tokens.at(0);
        if (cmd == "v")
        {
            Vertex vert;
            for (int i = 0; i<VERTEX_COORD_COUNT; i++)
            {
                vert.xyzCoords[i] = (GLfloat)atof(tokens.at(i+1).c_str());
            }
            vertices.push_back(&vert);
        }
        else if (cmd == "vn")
        {
            if (!SMOOTH_NORMALS_ENABLED)
            {
                GLfloat normal[] = {(GLfloat)atof(tokens.at(1).c_str()),(GLfloat)atof(tokens.at(2).c_str()),(GLfloat)atof(tokens.at(3).c_str())};
                normals.push_back(normal);
            }
        }
        else if (cmd == "vt")
        {
            GLfloat tc[] = {(GLfloat)atof(tokens.at(1).c_str()),(GLfloat)atof(tokens.at(2).c_str())};
            texCoords.push_back(tc);
        }
        else if (cmd == "f")
        {
            Triangle poly;
            for (int i=0; i<TRIANGLE_INDEX_COUNT; i++)
            {
                vector<string> indices;
                tokenize(tokens.at(i+1), iDelims, indices);
                poly.vertexIndices[i] = (GLshort)(atoi(indices.at(0).c_str())-1);
                if (!SMOOTH_NORMALS_ENABLED)
                {
                    poly.normalIndices[i] = (GLshort)(atoi(indices.at(2).c_str())-1);
                }
                if (textured)
                {
                    poly.texCoordIndices[i] = (GLshort)(atoi(indices.at(1).c_str())-1);
                }
            }
            triangles.push_back(&poly);
        }
    }
    destination->setVertices(vertices);
    destination->setTriangles(triangles);
    destination->setTextureCoords(texCoords);
    destination->setTextured(textured);
    if (SMOOTH_NORMALS_ENABLED)
    {
        destination->calcSmoothNormals();
    }
    else
    {
        destination->setNormals(normals);
    }
}