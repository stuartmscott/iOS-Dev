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
public:
    vector<GLfloat> parameters;
    Transform(TransformType transType, vector<GLfloat> &params);
    Transform(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3);
    Transform(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3, GLfloat param4);
    ~Transform();
    void execute();
};