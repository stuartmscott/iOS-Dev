//
//  Face.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Tile.h"
#import "Edge.h"

@interface Face : NSObject 

@property (retain) NSArray *tiles;

-(id)init;

-(void)setEdgesN:(Edge*)north E:(Edge*)east S:(Edge*)south W:(Edge*)west;

@end
