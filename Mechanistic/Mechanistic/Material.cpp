//
//  Material.cpp
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Material.h"
#include <OpenGLES/ES1/gl.h>

Material::Material()
{
    setAmbient(0.2f, 0.2f, 0.2f, 1.0f);
    setDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
    setSpecular(0, 0, 0, 1);
    setEmission(0, 0, 0, 1);
    shininess = 0;
}

Material::~Material()
{
    
}

void Material::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;
}

void Material::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;
}

void Material::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;
}

void Material::setEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    emission[0] = r;
    emission[1] = g;
    emission[2] = b;
    emission[3] = a;
}