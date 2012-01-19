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

@property float xRotation, yRotation;
@property (retain) NSArray *faces, *edges;
@property int spawnFace;
@property int spawnTile;
@property int targetFace;
@property int targetTile;

-(id)init;

//Recursive function - Given a gear which is spinning, it will set all neighbour gears to spin iff they aren't already spinning
-(void)setSpinningFrom:(int)faceIndex tileIndex:(int)tileIndex;

//Indexies
//Tile - top left is 0 bottom right is n
//Face - top face is 0, top edges ccw, then side faces and edges ccw, then bottom edges then bottom face

@end
