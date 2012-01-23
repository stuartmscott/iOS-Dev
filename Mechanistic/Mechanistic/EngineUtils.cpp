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

void appendToStringVector(string &fileName, vector<string>& container)
{
    string line;
    ifstream in(fileName.c_str());
    while (getline(in,line))
    {
        container.push_back(line);
    }
    in.close();
}

void appendToTxtFile(const string &fileName, const string &text)
{
    fstream out;
    out.open(fileName.c_str(), fstream::in | fstream::out | fstream::app);
    out<<text.c_str()<<"\n";
    out.close();
}