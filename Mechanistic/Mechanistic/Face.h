//
//  Face.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Tile.h"

@interface Face : NSObject 

//This will need references to its neighbour faces

@property (retain) NSArray *tiles;

@end
