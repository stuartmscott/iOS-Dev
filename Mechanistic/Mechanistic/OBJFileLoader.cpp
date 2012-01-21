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

void split(const char *str, char c, vector<string>& result)
{
    while(true)
    {
        const char *begin = str;        
        while(*str != c && *str)
            str++;
        result.push_back(string(begin, str));
        if(0 == *str++)
            break;
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
    char delims[] = " \r\n";
    vector<string> tokens;
    string line;
    ifstream in(fileName.c_str());
    string doubleSpace = "  ";
    string space = " ";
    while (getline(in,line))
    {
        trim(line);
        replaceAll(line, doubleSpace, space);
        tokens.clear();
        tokenize(line, delims, tokens);
        string cmd = tokens.at(0);
        if (cmd == "v")
        {
            Vertex* vert = (Vertex*)malloc(sizeof(Vertex));
            for (int i = 0; i<VERTEX_COORD_COUNT; i++)
            {
                vert->xyzCoords[i] = (GLfloat)atof(tokens.at(i+1).c_str());
            }
            vertices.push_back(vert);
        }
        else if (cmd == "vn")
        {
            if (!SMOOTH_NORMALS_ENABLED)
            {
                GLfloat* normal = (GLfloat*)malloc(sizeof(GLfloat)*3);
                normal[0] = (GLfloat)atof(tokens.at(1).c_str());
                normal[1] = (GLfloat)atof(tokens.at(2).c_str());
                normal[2] = (GLfloat)atof(tokens.at(3).c_str());
                normals.push_back(normal);
            }
        }
        else if (cmd == "vt")
        {
            GLfloat* tc = (GLfloat*)malloc(sizeof(GLfloat)*2);
            tc[0] = (GLfloat)atof(tokens.at(1).c_str());
            tc[1] = (GLfloat)atof(tokens.at(2).c_str());
            texCoords.push_back(tc);
        }
        else if (cmd == "f")
        {
            Triangle* poly = (Triangle*)malloc(sizeof(Triangle));
            for (int i=0; i<TRIANGLE_INDEX_COUNT; i++)
            {
                vector<string> indices;
                split(tokens.at(i+1).c_str(), '/', indices);
                poly->vertexIndices[i] = (GLshort)(atoi(indices.at(0).c_str())-1);
                if (!SMOOTH_NORMALS_ENABLED)
                {
                    string str = indices.at(2);
                    poly->normalIndices[i] = (GLshort)(atoi(str.c_str())-1);
                    /*if(poly->normalIndices[i]>60){
                        //uh oh
                        int kost = 0+2;
                    }*/
                }
                if (textured)
                {
                    poly->texCoordIndices[i] = (GLshort)(atoi(indices.at(1).c_str())-1);
                }
            }
            triangles.push_back(poly);
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