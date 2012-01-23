//
//  OBJFileLoader.h
//  Mechanistic
//
//  Created by Kostadin on 20/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "MeshNode.h"
#include <string>
#include <vector>

void loadMesh(const string &fileName, MeshNode * destination, bool textured);
void split(const char *str, char c, vector<string>& result);