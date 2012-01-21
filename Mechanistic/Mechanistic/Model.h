//
//  Model.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Face.h"
#define MOVE_PLAY 5.0f
#define WIDTH 320.0f
#define HEIGHT 480.0f
#define NEAR_CLIP 0.01f
#define FAR_CLIP 100.0f

@interface Model : NSObject {
    float eye[3], up[3];
    float radius, theta, phi;
    bool isDragging;
}

@property bool inGame;
@property CGPoint start, current;
@property (retain) NSArray *faces, *edges;
@property int spawnFace, spawnTile;
@property int targetFace, targetTile;

-(id)init;

-(float*)getEye;

-(float*)getUp;

@end
