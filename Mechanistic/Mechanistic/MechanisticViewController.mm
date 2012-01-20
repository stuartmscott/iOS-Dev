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

@synthesize animating, context, displayLink, model;

-(void)slideTile:(int)faceIndex From:(int)oldIndex To:(int)newIndex{
    //TODO this assumes that the tile at the old index is not empty and the tile at the new index is
    //this will be used to move the tiles when the user taps them
}

- (void)awakeFromNib
{
    EAGLContext * aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    
    if (!aContext)
        NSLog(@"Failed to create ES context");
    else if (![EAGLContext setCurrentContext:aContext])
        NSLog(@"Failed to set ES context current");
    
	self.context = aContext;
	[aContext release];
    
    self.model = [[Model alloc] init];
    ((EAGLView *)self.view).model = model;
    
    [(EAGLView *)self.view setContext:context];
    [(EAGLView *)self.view setFramebuffer];
    
    [self initGLSettings];
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
    [model release];
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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    //glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    
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
    
    glFrustumf(left, right, bottom, top, NEAR_CLIP, FAR_CLIP);
    glMatrixMode(GL_MODELVIEW);
}

-(float)toRadians:(float)degrees {
    return degrees * (180.0f / M_PI);
}

- (void)drawFrame
{
    [(EAGLView *)self.view setFramebuffer];
    
    /* Rendering + */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* Camera + */
    float* eye = [self.model getEye];
    float* up = [self.model getUp]; 
    gluLookAt(eye[0], eye[1], eye[2], 0.0f, 0.0f, 0.0f, up[0], up[1], up[2]);
    /* Camera - */
    static bool loaded = false;
    static MeshNode* gear = new MeshNode();
    if (!loaded)
    {
        NSString *nsGearPath = [[NSBundle mainBundle] pathForResource:@"Gear" ofType:@"obj"];
        string realm = [nsGearPath cStringUsingEncoding:[NSString defaultCStringEncoding]];
        loadMesh(realm, gear, false);
        loaded = true;
    }
    
    glPushMatrix();
    {
        SceneGraphNode* sceneGraph = new SceneGraphNode();
        MeshNode* mesh = new MeshNode();
        vector<Vertex*> vertices;
        vector<GLfloat*> normals;
        vector<Triangle*> triangles;
        
        Vertex top;
        top.xyzCoords[0] = 0;
        top.xyzCoords[1] = 0.5f;
        top.xyzCoords[2] = -1;
        Vertex left;
        left.xyzCoords[0] = -0.5f;
        left.xyzCoords[1] = -0.5f;
        left.xyzCoords[2] = -1;
        Vertex right;
        right.xyzCoords[0] = 0.5f;
        right.xyzCoords[1] = -0.5f;
        right.xyzCoords[2] = -1;
        vertices.push_back(&left);
        vertices.push_back(&right);
        vertices.push_back(&top);
        
        GLfloat n0[3] = {0, 0, 1};
        normals.push_back(n0);
        
        Triangle triangle;
        triangle.normalIndices[0] = 0;
        triangle.normalIndices[1] = 0;
        triangle.normalIndices[2] = 0;
        triangle.vertexIndices[0] = 0;
        triangle.vertexIndices[1] = 1;
        triangle.vertexIndices[2] = 2;
        
        triangles.push_back(&triangle);
        mesh->setVertices(vertices);
        mesh->setNormals(normals);
        mesh->setTriangles(triangles);
        mesh->material->setAmbient(1, 1, 1, 1);
        LightNode* light = new LightNode();
        light->spotlight = true;
        vector<SceneGraphNode*> children;
        children.push_back(light);
        children.push_back(mesh);
        vector<Transform*> transes;
        vector<GLfloat> params;
        params.push_back(0.2f);
        params.push_back(0.2f);
        params.push_back(0.2f);
        Transform * trans = new Transform(SCALE, params);
        transes.push_back(trans);
        TransformNode* scaleNode = new TransformNode(transes);
        scaleNode->getChildren()->push_back(gear);
        children.push_back(scaleNode);
        sceneGraph->setChildren(children);
        render(sceneGraph);
        delete mesh;
        delete sceneGraph;
    }
    glPopMatrix();
    /* Rendering - */
    
    [(EAGLView *)self.view presentFramebuffer];
}

@end