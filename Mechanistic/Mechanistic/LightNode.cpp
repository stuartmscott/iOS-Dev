//
//  LightNode.cpp
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "LightNode.h"
#include <OpenGLES/ES1/gl.h>

LightNode::LightNode()
{
    visitedByDeath = false;
    index = 0;
    spotlight = false;
    enabled = true;
    setPosition(0, 0, 1);
    setAmbientColour(0, 0, 0, 1);
    setDiffuseColour(1, 1, 1, 1);
    setSpecularColour(1, 1, 1, 1);//1 1 1 1
    setSpotDirection(0, 0, -1);
    spotExponent = 0;
    spotCutoffAngle = 15;
    constantAttenuation = 1;
    linearAttenuation = 0;
    quadraticAttenuation = 0;
}

LightNode::~LightNode()
{
    
}

void LightNode::doBeforeRender()
{
    int lightID = GL_LIGHT0 + index;
    GLfloat lightPos[4] = { position[0], position[1], position[2], ((spotlight) ? 1 : 0) };
    glLightfv(lightID, GL_POSITION, (const GLfloat*)lightPos);
    glLightfv(lightID, GL_AMBIENT, (const GLfloat*)ambientColour);
    glLightfv(lightID, GL_DIFFUSE, (const GLfloat*)diffuseColour);
    glLightfv(lightID, GL_SPECULAR, (const GLfloat*)specularColour);
    glLightx(lightID, GL_SPOT_CUTOFF, spotCutoffAngle);
    glLightfv(lightID, GL_SPOT_DIRECTION, (const GLfloat*)spotDirection);
    glLightx(lightID, GL_SPOT_EXPONENT, spotExponent);
    glLightx(lightID, GL_CONSTANT_ATTENUATION, constantAttenuation);
    glLightx(lightID, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightx(lightID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    if (enabled)
    {
        glEnable(lightID);
    }
    else
    {
        glDisable(lightID);
    }
}

void LightNode::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void LightNode::setAmbientColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    ambientColour[0] = r;
    ambientColour[1] = g;
    ambientColour[2] = b;
    ambientColour[3] = a;    
}

void LightNode::setDiffuseColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    diffuseColour[0] = r;
    diffuseColour[1] = g;
    diffuseColour[2] = b;
    diffuseColour[3] = a;
}

void LightNode::setSpecularColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    specularColour[0] = r;
    specularColour[1] = g;
    specularColour[2] = b;
    specularColour[3] = a;
}

void LightNode::setSpotDirection(GLfloat x, GLfloat y, GLfloat z)
{
    spotDirection[0] = x;
    spotDirection[1] = y;
    spotDirection[2] = z;
}