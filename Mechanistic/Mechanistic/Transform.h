//
//  Transform.h
//  Mechanistic
//
//  Created by Kostadin on 17/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <vector>
#include <OpenGLES/ES1/gl.h>

using namespace std;

typedef enum {
    TRANSLATE, SCALE, ROTATE
} TransformType;

class Transform
{
private:
    TransformType type;
    vector<float> parameters;
public:    
    Transform(TransformType transType, vector<float> params);
    ~Transform();
    void execute();
};