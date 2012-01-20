//
//  Model.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Face.h"

@interface Model : NSObject

@property CGPoint start, current;
@property float xRotation, yRotation;
@property (retain) NSArray *faces, *edges;
@property int spawnFace;
@property int spawnTile;
@property int targetFace;
@property int targetTile;

-(id)init;

//Recursive function - Given a gear which is spinning, it will set all neighbour gears to spin iff they aren't already spinning
-(void)setSpinningFrom:(int)faceIndex tileIndex:(int)tileIndex;

-(void)touchesStart:(CGPoint)point;

-(void)touchesMoved:(CGPoint)point;//TODO the distance moved will be used to determine the rotation

-(void)touchesEnd;

@end
