//
//  Transform.cpp
//  Mechanistic
//
//  Created by Kostadin on 17/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Transform.h"
#include <OpenGLES/ES2/gl.h>
#include "EngineUtils.h"
#include <string>
#include <math.h>

Transform::Transform(TransformType transType, vector<float> params)
{
    type = transType;
    parameters = params;
    compiled = false;
    program = 0;
    vertexShader = 0;    
}

void Transform::compile()
{
    program = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char* source = file2charArray("Transform.vsh");
    glShaderSource(vertexShader, 1, (const GLchar**)source, NULL);
    glCompileShader(vertexShader);
    glAttachShader(program, vertexShader);
    glLinkProgram(program);
    matrixUniform = glGetUniformLocation(program, "matrix");
}

void Transform::execute()
{
    if (!compiled)
    {
        compile();
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;i<4;j++)
        {
            if (i!=j)
            {
                matrix[i][j]=0;
            }
            else
            {
                matrix[i][j]=1;
            }
        }
    }

    switch (type)
    {
        case TRANSLATE:            
            matrix[0][3] = parameters.at(0);
            matrix[1][3] = parameters.at(1);
            matrix[2][3] = parameters.at(2);
            break;
        case SCALE:
            matrix[0][0] = parameters.at(0);
            matrix[1][1] = parameters.at(1);
            matrix[2][2] = parameters.at(2);
            break;
        case ROTATE:
            GLfloat angle = parameters.at(0);
            GLfloat x = parameters.at(1);
            GLfloat y = parameters.at(2);
            GLfloat z = parameters.at(3);
            GLfloat c = cos(angle);
            GLfloat s = sin(angle);
            matrix[0][0] = x*x*(1-c)*c;
            matrix[0][1] = x*y*(1-c)-z*s;
            matrix[0][2] = x*z*(1-c)+y*s;
            matrix[1][0] = y*x*(1-c)+z*s;
            matrix[1][1] = y*y*(1-c)+c;
            matrix[1][2] = y*z*(1-c)-x*s;
            matrix[2][0] = x*z*(1-c)-y*s;
            matrix[2][1] = y*z*(1-c)+x*s;
            matrix[2][2] = z*z*(1-c)+c;
            break;
    }
    glUniformMatrix4fv(matrixUniform, 1, false, (const GLfloat*) &matrix);
    glUseProgram(program);
}