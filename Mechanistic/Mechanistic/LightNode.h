//
//  LightNode.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "SceneGraphNode.h"
#include <OpenGLES/ES1/gl.h>
#define MAX_LIGHTS 8


class LightNode:SceneGraphNode
{
public:
    GLenum index;
    bool enabled;
    bool spotlight;
    GLfloat position[3];
    GLfloat ambientColour[4];
    GLfloat diffuseColour[4];
    GLfloat specularColour[4];
    GLfloat spotDirection[3];
    GLenum spotExponent;
    GLenum spotCutoffAngle;
    GLenum constantAttenuation;
    GLenum linearAttenuation;
    GLenum quadraticAttenuation;
    LightNode();
    ~LightNode();
    void doBeforeRender();
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void setAmbientColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setDiffuseColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecularColour(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpotDirection(GLfloat x, GLfloat y, GLfloat z);
};