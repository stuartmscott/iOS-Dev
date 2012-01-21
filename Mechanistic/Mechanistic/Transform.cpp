//
//  Transform.cpp
//  Mechanistic
//
//  Created by Kostadin on 17/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Transform.h"
#include <OpenGLES/ES1/gl.h>

Transform::Transform(TransformType transType, vector<GLfloat> &params)
{
    type = transType;
    for (int i=0; i<params.size();i++)
    {
        parameters.push_back(params.at(i));
    }
}

Transform::Transform(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3)
{
    type = transType;
    parameters.clear();
    parameters.push_back(param1);
    parameters.push_back(param2);
    parameters.push_back(param3);
}

Transform::Transform(TransformType transType, GLfloat param1, GLfloat param2, GLfloat param3, GLfloat param4)
{
    type = transType;
    parameters.clear();
    parameters.push_back(param1);
    parameters.push_back(param2);
    parameters.push_back(param3);
    parameters.push_back(param4);
}

Transform::~Transform()
{

}

void Transform::execute()
{

    switch (type)
    {
        case TRANSLATE:            
            glTranslatef(parameters.at(0), parameters.at(1), parameters.at(2));
            break;
        case SCALE:
            glScalef(parameters.at(0), parameters.at(1), parameters.at(2));
            break;
        case ROTATE:
            glRotatef(parameters.at(0), parameters.at(1), parameters.at(2), parameters.at(3));
            break;
    }
}