//
//  Edge.h
//  Mechanistic
//
//  Created by Kostadin on 19/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Tile.h"

@class Face;

@interface Edge : NSObject

@property (retain) NSArray *tiles;

-(id)init;

-(void)setFacesN:(Face*)north S:(Face*)south;

@end
