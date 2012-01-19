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