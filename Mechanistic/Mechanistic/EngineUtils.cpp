//
//  EngineUtils.cpp
//  Mechanistic
//
//  Created by Kostadin on 17/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "EngineUtils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char* file2charArray(string fileName)
{
    string buf;
    string line;
    ifstream in(fileName.c_str());
    while (getline(in,line))
    {
        buf += line + "\n";
    }
    char* result = new char[buf.size()+1];
    strcpy(result, buf.c_str());
    return result;
}