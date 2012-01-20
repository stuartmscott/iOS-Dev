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
    char doubleSpace[] = "  ";
    char space[] = " ";
    while (getline(in,line))
    {
        //std::replace(line.begin(), line.end(), doubleSpace, space);
        
    }
}