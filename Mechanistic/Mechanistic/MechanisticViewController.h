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
    void* converter;
    void* sceneGraph;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
@property (nonatomic, retain) IBOutlet UIWindow *window;

-(float)toRadians:(float)degrees;

-(void)startAnimation;
-(void)stopAnimation;

-(void)calcEyePosition;
-(void)dragEnded;
@end
