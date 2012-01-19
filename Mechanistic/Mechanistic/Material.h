//
//  Material.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#pragma once
#include <OpenGLES/ES1/gl.h>

class Material
{
public:
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat emission[4];
    GLfloat shininess;
    Material();
    ~Material();
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
};