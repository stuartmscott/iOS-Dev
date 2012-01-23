//
//  LevelReader.cpp
//  Mechanistic
//
//  Created by Kostadin on 23/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "LevelReader.h"
#include "FaceAndEdge.h"
#include <iostream>
#include <fstream>

using namespace std;

int * readLevel(string &fileName)
{
    int runs = 6*TILES_PER_FACE+12*TILES_PER_EDGE;
    int* level = (int*)malloc(sizeof(int)*runs);
    ifstream fileInput(fileName.c_str());
    for (int i=0; i<runs; i++)
    {
        fileInput>>level[i];
    }
    fileInput.close();
    return level;
}