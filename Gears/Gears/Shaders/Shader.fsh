//
//  Shader.fsh
//  Gears
//
//  Created by Kostadin on 12/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
