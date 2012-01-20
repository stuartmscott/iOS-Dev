//
//  Model.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Model.h"

@implementation Model

@synthesize faces, edges, spawnFace, spawnTile, targetFace, targetTile;
@synthesize start, current;

- (id)init {
    self = [super init];
    if (self) {
        //Top face
        Face *top = [[Face alloc] init];
        
        //Top edges
        Edge *te0 = [[Edge alloc] init];
        Edge *te1 = [[Edge alloc] init];
        Edge *te2 = [[Edge alloc] init];
        Edge *te3 = [[Edge alloc] init];
        
        //Side faces
        Face *sf0 = [[Face alloc] init];
        Face *sf1 = [[Face alloc] init];
        Face *sf2 = [[Face alloc] init];
        Face *sf3 = [[Face alloc] init];
        
        //Side edges
        Edge *se0 = [[Edge alloc] init];
        Edge *se1 = [[Edge alloc] init];
        Edge *se2 = [[Edge alloc] init];
        Edge *se3 = [[Edge alloc] init];
        
        //Bottom edges
        Edge *be0 = [[Edge alloc] init];
        Edge *be1 = [[Edge alloc] init];
        Edge *be2 = [[Edge alloc] init];
        Edge *be3 = [[Edge alloc] init];
        
        //Bottom face
        Face *bot = [[Face alloc] init];
        
        [top setEdgesN: te2 E: te1 S: te0 W: te3];
        
        [te0 setFacesN: top S:sf0];
        [te1 setFacesN: top S:sf1];
        [te2 setFacesN: top S:sf2];
        [te3 setFacesN: top S:sf3];
        
        [sf0 setEdgesN: te0 E: se0 S: be0 W: se3];
        [sf1 setEdgesN: te1 E: se1 S: be1 W: se0];
        [sf2 setEdgesN: te2 E: se2 S: be2 W: se1];
        [sf3 setEdgesN: te3 E: se3 S: be3 W: se2];
        
        [se0 setFacesN: sf1 S:sf0];
        [se1 setFacesN: sf2 S:sf1];
        [se2 setFacesN: sf3 S:sf2];
        [se3 setFacesN: sf0 S:sf3];
        
        [te0 setFacesN: sf0 S: bot];
        [te1 setFacesN: sf1 S: bot];
        [te2 setFacesN: sf2 S: bot];
        [te3 setFacesN: sf3 S: bot];
        
        [bot setEdgesN: te0 E: te1 S: te2 W: te3];
        
        self.faces = [NSArray arrayWithObjects: top, sf0, sf1, sf2, sf3, bot, nil];
        
        radius = 1.0f;
        theta = -0.7f;
        phi = 0.5f;
        [self calcEyePosition];
    }
    return self;
}

-(void)setSpinningFrom:(int)faceIndex tileIndex:(int)tileIndex{
    //TODO
}

-(void)touchesStart:(CGPoint)point {
    self.start = point;
    isDragging = false;
}

//Adapted from code from Dr. Steve Maddock
-(void)touchesMoved:(CGPoint)point {
    float dx = (point.x - start.x);
    float dy = (point.y - start.y);
    if (!isDragging) {
        float distMoved = sqrtf((dx*dx)+(dy*dy));
        NSLog(@"distMoved %f", distMoved);
        if(distMoved <= MOVE_PLAY)
            return;
        isDragging = true;
    }
    
    self.current = point;
    theta -= (dx / WIDTH) *2.0f;
    phi += (dy / HEIGHT) * 2.0f;
    [self calcEyePosition];
    self.start = current;
}

-(void)touchesEnd {
    if (!isDragging) {
        //TODO generate a click
    }
}

//Adapted from code from Dr. Steve Maddock
-(void)calcEyePosition {
    float cy, cz, sy, sz;
    cy = cosf(theta);
    sy = sinf(theta);
    cz = sinf(phi);
    sz = sinf(phi);
    
    eye[0] = radius * cy * cz;
    eye[1] = radius *sz;
    eye[2] = - radius * sy *cz;
    
    up[0] = -cy *sz;
    up[1] = cz;
    up[2] = sy *sz;
    
    if(up[1]<0){
        up[0] = -up[0];
        up[1] = -up[1];
        up[2] = -up[2];
    }
}

-(float*)getEye {
    return eye;
}

-(float*)getUp {
    return up;
}

- (void)dealloc {
    for (Face *f in faces)
        [f dealloc];
    [faces dealloc];
    [super dealloc];
}

@end