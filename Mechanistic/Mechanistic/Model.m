//
//  Model.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Model.h"


@implementation Model

@synthesize xRotation, yRotation, faces, edges, spawnFace, spawnTile, targetFace, targetTile;

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
        Face *sd0 = [[Face alloc] init];
        Face *sd1 = [[Face alloc] init];
        Face *sd2 = [[Face alloc] init];
        Face *sd3 = [[Face alloc] init];
        
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
        
        [te0 setFacesN: top S:se0];
        [te1 setFacesN: top S:se1];
        [te2 setFacesN: top S:se2];
        [te3 setFacesN: top S:se3];
        
        [sd0 setEdgesN: te0 E: se0 S: be0 W: se3];
        [sd1 setEdgesN: te1 E: se1 S: be1 W: se0];
        [sd2 setEdgesN: te2 E: se2 S: be2 W: se1];
        [sd3 setEdgesN: te3 E: se3 S: be3 W: se2];
        
        [se0 setFacesN: sd1 S:sd0];
        [se1 setFacesN: sd2 S:sd1];
        [se2 setFacesN: sd3 S:sd2];
        [se3 setFacesN: sd0 S:sd3];
        
        [te0 setFacesN: se0 S: bot];
        [te1 setFacesN: se1 S: bot];
        [te2 setFacesN: se2 S: bot];
        [te3 setFacesN: se3 S: bot];
        
        [bot setEdgesN: te0 E: te1 S: te2 W: te3];
        
        self.faces = [NSArray arrayWithObjects: top, sd0, sd1, sd2, sd3, bot, nil];
    }
    return self;
}

-(void)setSpinningFrom:(int)faceIndex tileIndex:(int)tileIndex{
    //TODO
}

- (void)dealloc {
    for (Face *f in faces)
        [f dealloc];
    [faces dealloc];
    [super dealloc];
}

@end