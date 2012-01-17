//
//  Transform.h
//  Mechanistic
//
//  Created by Kostadin on 17/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <vector>
#include <OpenGLES/ES2/gl.h>

using namespace std;

typedef enum {
    TRANSLATE, SCALE, ROTATE
} TransformType;

class Transform
{
private:
    GLuint program;
    GLuint vertexShader;
    GLuint matrixUniform;
    TransformType type;
    vector<float> parameters;
    GLfloat matrix[4][4];
    bool compiled;
    void compile();
public:    
    Transform(TransformType transType, vector<float> params);
    ~Transform();
    void execute();
};