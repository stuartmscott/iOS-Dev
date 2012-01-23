//
//  EngineUtils.h
//  Mechanistic
//
//  Created by Kostadin on 17/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

char* file2charArray(string fileName);
void appendToTxtFile(const string &fileName, const string &text);
void appendToStringVector(string &fileName, vector<string>& container);