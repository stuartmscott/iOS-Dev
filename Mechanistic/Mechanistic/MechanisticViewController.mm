//
//  MechanisticViewController.m
//  Mechanistic
//
//  Created by Kostadin on 29/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "MechanisticViewController.h"
#import "EAGLView.h"
#import "LightNode.h"
#import "MeshNode.h"
#import "SceneGraphNode.h"
#import "SceneGraphRenderer.h"
#import "TransformNode.h"
#import <vector>
#import <string>
#import "OBJFileLoader.h"
#import "Model.h"
#import "Converter.h"
#import "Destroyer.h"
#import "LevelReader.h"

// Uniform index.
enum {
    UNIFORM_TRANSLATE,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};

@interface MechanisticViewController () 
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
- (void) initGLSettings;
@end

@implementation MechanisticViewController

@synthesize animating, context, displayLink, window;

- (void)viewDidLoad
{
    EAGLContext * aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    
    if (!aContext)
        NSLog(@"Failed to create ES context");
    else if (![EAGLContext setCurrentContext:aContext])
        NSLog(@"Failed to set ES context current");
    
	self.context = aContext;
	[aContext release];
    NSString *nsGearPath = [[NSBundle mainBundle] resourcePath];
    string directory = [nsGearPath cStringUsingEncoding:[NSString defaultCStringEncoding]];
    string lvl1 = directory+"/1.lvl";
    //string lvl1 = directory+"/test.lvl";
    int * level = readLevel(lvl1);
    model = new Model(level);
    delete level;
    [self calcEyePosition];
    
    [(EAGLView *)self.view setContext:context];
    [(EAGLView *)self.view setFramebuffer];
    
    [self initGLSettings];

    converter = new Converter(directory);
    
    animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
}

- (void)dealloc
{    
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    [context release];
    delete (Converter*)converter;
    delete (Model*)model;
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
    
    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	self.context = nil;	
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1) {
        animationFrameInterval = frameInterval;
        
        if (animating) {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating) {
        CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(drawFrame)];
        [aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.displayLink = aDisplayLink;
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating) {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

- (void)initGLSettings
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisable(GL_TEXTURE_2D);
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        glDisable(GL_LIGHT0 + i);
    }
    //Camera
    float fAspect = (float) WIDTH / HEIGHT;
    float fovy = 45.0f;
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float top = tanf([self toRadians: (fovy * 0.5f)]) * NEAR_CLIP;
    float bottom = -top;
    float left = fAspect * bottom;
    float right = fAspect * top;
    
    NSLog(@"t:%f, b:%f, l:%f, r:%f", top, bottom, left, right);
    
    Model * _model = (Model*) model;
    float cubeHeight = (SCALE_FACTOR * TILE_HEIGHT * 3.0f) + (SCALE_FACTOR * TILE_GAP * 2.0f);
    float camToCube = _model->radius - (SCALE_FACTOR * FACE_DISTANCE_FROM_ORIGIN);
    float cubeSize = 2.0f*((cubeHeight/2.0f)*(NEAR_CLIP/(NEAR_CLIP+camToCube)));
    _model->screenCubeSize = (cubeSize/(2.0f*top))*HEIGHT;
    _model->screenCubeX = (WIDTH - _model->screenCubeSize)/2.0f;
    _model->screenCubeY = (HEIGHT - _model->screenCubeSize)/2.0f;
    
    glFrustumf(left, right, bottom, top, NEAR_CLIP, FAR_CLIP);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    //glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

-(float)toRadians:(float)degrees {
    return degrees * (180.0f / M_PI);
}

- (float)signf:(float) val{
    if(val<0)
        return -1.0f;
    return 1.0f;        
}

- (int) mod:(int)number by:(int) modulus{
    int result = number % modulus;
    if (result < 0) result += modulus;
    return result;
}

- (void)update {
    Model * _model = (Model*) model;
    //if target gear is spinning, game won
    int faceIndex = _model->targetTileFace;
    int tileIndex = _model->targetTileIndex;
    if (_model->faces[faceIndex]->tiles[tileIndex]->gear->isSpinning)
        _model->gameWon = true;
    if (_model->gameWon) {
        _model->theta += 0.01f;
        _model->phi += 0.01f;
        [self calcEyePosition];
    } else if (_model->isSnapping) {
        float dT = _model->destTheta - _model->theta;
        if (fabsf(dT)<SNAP_INTERVAL)
            _model->theta = _model->destTheta;
        else
            _model->theta += [self signf: dT]*SNAP_INTERVAL;
        float dP = _model->destPhi - _model->phi;
        if (fabsf(dP)<SNAP_INTERVAL)
            _model->phi = _model->destPhi;
        else
            _model->phi += [self signf: dP]*SNAP_INTERVAL;
        if((_model->theta == _model->destTheta)&&(_model->phi == _model->destPhi))
            _model->isSnapping = false;
        [self calcEyePosition];
    }
    
    Face* f;
    Edge* e;
    Tile* t;
    //Reset all gears to not spinning
    for(int i = 0; i<6;i++){
        f = _model->faces[i];
        for(int j = 0;j<9;j++){
            t = f->tiles[j];
            if (t->hasGear){
                t->gear->isSpinning = false;
                if (j%2==0)
                    t->gear->rotation = 0;
                else
                    t->gear->rotation = NEIGHBOUR_DIFFERENCE;
            }
        }
    }
    for(int i = 0; i<12;i++){
        e = _model->edges[i];
        for(int j = 0;j<3;j++){
            t = e->tiles[j];
            if (t->hasGear){
                t->gear->isSpinning = false;
                if (j%2==1)
                    t->gear->rotation = 0;
                else
                    t->gear->rotation = NEIGHBOUR_DIFFERENCE;
            }
        }
    }
    
    //Set spawn gear to spinning
    faceIndex = _model->spawnTileFace;
    tileIndex = _model->spawnTileIndex;
    float spawnRotation = _model->spawnRotation += GEAR_SPEED;
    _model->faces[faceIndex]->setTileSpinning(tileIndex, spawnRotation);
    
    sceneGraph = ((Converter*)converter)->convert(_model);
}

- (void)drawFrame
{
    [self update];
    
    if (sceneGraph)
    {
        [(EAGLView *)self.view setFramebuffer];
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        
        Model * _model = (Model*) model;
        float* eye = _model->eye;
        float* up = _model->up;
        
        static bool loaded = false;
        static LightNode* light;
        if (!loaded)
        {
            light = new LightNode();
            light->spotlight = false;
            light->setPosition(1.0f, 1.0f, 6000.0f);
            light->setSpecularColour(0.4f, 0.4f, 0.4f, 1.0f);
            light->setSpotDirection(0, 0, 0);
            loaded = true;
        }
        light->doBeforeRender();
        gluLookAt(eye[0], eye[1], eye[2], 0.0f, 0.0f, 0.0f, up[0], up[1], up[2]);
        if (sceneGraph) {
            glPushMatrix();
            {
                render((SceneGraphNode*) sceneGraph);
                //Destroyer of worlds
                annihilate((SceneGraphNode*)sceneGraph, false);
                sceneGraph = 0;
            }
            glPopMatrix();
        }
        
        [(EAGLView *)self.view presentFramebuffer];
    }
}

-(void)gameClick:(CGPoint) point {
    Model * _model = (Model*) model;
    float cubeX = point.x - _model->screenCubeX;
    float cubeY = point.y - _model->screenCubeY;
    float cubeSize = _model->screenCubeSize;
    float tileSize = cubeSize/3;
    if (cubeX<=cubeSize&&cubeX>=0&&cubeY<=cubeSize&&cubeY>=0) {
        float limit = sqrtf((_model->radius*_model->radius)/2.0f);
        float* eye = _model->eye;
        float* up = _model->up;
        int col = cubeX/tileSize;
        int row = cubeY/tileSize;
        int relativeTileIndex = (row*3) + col;
        int faceRotation;
        int faceIndex;
        int tileIndex;
        //NSLog(@"%f %f %f",up[0], up[1], up[2]);
        if (eye[1]>=limit) {
            //  0  0 -1 = 0
            //  1  0  0 = 90
            //  0  0  1 = 180
            //  -1 0  0 = 270
            if(up[2]<-0.5f)
                faceRotation = 0;
            else if(up[0]>0.5f)
                faceRotation = 90;
            else if(up[2]>0.5f)
                faceRotation = 180;
            else
                faceRotation = 270;
            faceIndex = 0;
            //NSLog(@"LOOKING AT TOP");
        } else if (eye[1]<=-limit) {
            //  0  0  1 = 0
            //  1  0  0 = 90
            //  0  0 -1 = 180
            // -1  0  0 = 270
            if(up[2]>0.5f)
                faceRotation = 0;
            else if(up[0]>0.5f)
                faceRotation = 90;
            else if(up[2]<-0.5f)
                faceRotation = 180;
            else
                faceRotation = 270;
            faceIndex = 5;
            //NSLog(@"LOOKING AT BOTTOM");
        } else if (eye[0]>=limit) {
            //  0  1  0 = 0
            //  0 -1  0 = 180
            faceIndex = 2;
            faceRotation = (up[1]<-0.5f)?180:0;
            //NSLog(@"LOOKING AT SIDE 2");
        } else if (eye[0]<=-limit) {
            //  0  1  0 = 0
            //  0 -1  0 = 180
            faceIndex = 4;
            faceRotation = (up[1]<-0.5f)?180:0;
            //NSLog(@"LOOKING AT SIDE 4");
        } else if (eye[2]>=limit) {
            //  0  1  0 = 0
            //  0  -1 0 = 180
            faceIndex = 1;
            faceRotation = (up[1]<-0.5f)?180:0;
            //NSLog(@"LOOKING AT SIDE 1");
        } else {
            //  0  1  0 = 0
            //  0 -1  0 = 180
            faceIndex = 3;
            faceRotation = (up[1]<-0.5f)?0:180;
            //NSLog(@"LOOKING AT SIDE 3");
        }
        if (faceRotation==0) {
            tileIndex = relativeTileIndex;
        }else if(faceRotation==180){
            tileIndex = 8-relativeTileIndex;
        }else if(faceRotation==90){
            int translate []={2,5,8,1,4,7,0,3,6};
            tileIndex = translate[relativeTileIndex];
        }else{
            int translate []={6,3,0,7,4,1,8,5,2};
            tileIndex = translate[relativeTileIndex];
        }
        NSLog(@"Rotation: %d, Relative: %d, Tile: %d", faceRotation, relativeTileIndex, tileIndex);
        
        Face *currentFace = _model->faces[faceIndex];
        Tile *currentTile = currentFace->tiles[tileIndex];
        
        if (currentFace->isNextToFree(tileIndex)&&currentTile->moveable)
            currentFace->moveTile(tileIndex);
    }
}

//Adapted from code from Dr. Steve Maddock
-(void)calcEyePosition {
    Model * _model = (Model*) model;
    float cy, cz, sy, sz;
    cy = cosf(_model->theta);
    sy = sinf(_model->theta);
    cz = cosf(_model->phi);
    sz = sinf(_model->phi);
    
    _model->eye[0] = _model->radius * cy * cz;
    _model->eye[1] = _model->radius * sz;
    _model->eye[2] = -_model->radius * sy * cz;
    
    _model->up[0] = -cy * sz;
    _model->up[1] = cz;
    _model->up[2] = sy * sz;
}

-(void)dragEnded {
    Model * _model = (Model*) model;
    _model->isSnapping = true;
    float theta = _model->theta;
    float phi = _model->phi;
    _model->destTheta = ((int)((theta+[self signf:theta]*M_PI_4)/M_PI_2))*M_PI_2;
    _model->destPhi = ((int)((phi+[self signf:phi]*M_PI_4)/M_PI_2))*M_PI_2;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    Model * _model = (Model*) model;
    if (_model->gameWon||_model->isSnapping)
        return;
	UITouch *touch = [touches anyObject];
	CGPoint point = [touch locationInView:self.view];
    _model->startX = point.x;
    _model->startY = point.y;
    _model->isDragging = false;
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
    Model * _model = (Model*) model;
    if (_model->gameWon||_model->isSnapping)
        return;
	UITouch *touch = [touches anyObject];
	CGPoint point = [touch locationInView:self.view];
    
    //Adapted from code from Dr. Steve Maddock
    float dx = (point.x - _model->startX);
    float dy = (point.y - _model->startY);
    if (!_model->isDragging) {
        float distMoved = sqrtf((dx*dx)+(dy*dy));
        if(distMoved <= MOVE_PLAY)
        {
            return;
        }
        _model->isDragging = true;
    }
    //If the camera is upside down, reverse x
    if(_model->up[1]<0)
        dx = -dx;
        
    _model->currX = point.x;
    _model->currY = point.y;
    _model->theta -= (dx / WIDTH) * 2.0f;
    _model->phi += (dy / HEIGHT) * 2.0f;
    [self calcEyePosition];
    _model->startX = _model->currX;
    _model->startY = _model->currY;
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    Model * _model = (Model*) model;
    if (_model->gameWon||_model->isSnapping)
        return;
	UITouch *touch = [touches anyObject];
	CGPoint point = [touch locationInView:self.view];
    if (_model->isDragging)
        [self dragEnded];
    else
        [self gameClick: point];
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{
    Model * _model = (Model*) model;
    if (_model->gameWon||_model->isSnapping)
        return;
	UITouch *touch = [touches anyObject];
	CGPoint point = [touch locationInView:self.view];
    if (_model->isDragging)
        [self dragEnded];
    else
        [self gameClick: point]; 
}

@end