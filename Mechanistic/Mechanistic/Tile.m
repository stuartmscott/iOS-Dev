//
//  Tile.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Tile.h"


@implementation Tile

@synthesize empty, gear;

-(bool)hasGear{
    return (gear!=nil);
}

- (void)dealloc {
    if ([self hasGear])
        [gear dealloc];
    [super dealloc];
}

@end
