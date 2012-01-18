//
//  Model.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Model.h"


@implementation Model

@synthesize faces, spawnFace, spawnTile, targetFace, targetTile;

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