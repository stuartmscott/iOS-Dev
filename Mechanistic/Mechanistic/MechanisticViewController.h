//
//  MechanisticViewController.h
//  Mechanistic
//
//  Created by Kostadin on 29/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "gluLookAt.h"

@interface MechanisticViewController : UIViewController {
@private
    EAGLContext *context;
    GLuint program;
    BOOL animating;
    NSInteger animationFrameInterval;
    CADisplayLink *displayLink;
    void* model;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

-(void)slideTile:(int)faceIndex From:(int) oldIndex To:(int) newIndex;

-(float)toRadians:(float)degrees;

-(void)startAnimation;
-(void)stopAnimation;

-(void)calcEyePosition;
-(void)gameClick:(CGPoint) point;
-(void)menuClick:(CGPoint) point;
@end
