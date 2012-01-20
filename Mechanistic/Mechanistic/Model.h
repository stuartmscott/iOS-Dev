//
//  Model.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Face.h"

@interface Model : NSObject {
    float eye[3], up[3];
    float radius, theta, phi;
}

@property CGPoint start, current;
@property (retain) NSArray *faces, *edges;
@property int spawnFace, spawnTile;
@property int targetFace, targetTile;

-(id)init;

//Recursive function - Given a gear which is spinning, it will set all neighbour gears to spin iff they aren't already spinning
-(void)setSpinningFrom:(int)faceIndex tileIndex:(int)tileIndex;

-(void)calcEyePosition;

-(void)touchesStart:(CGPoint)point;

-(void)touchesMoved:(CGPoint)point;//TODO the distance moved will be used to determine the rotation

-(void)touchesEnd;

@end
