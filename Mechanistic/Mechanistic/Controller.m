//
//  Controller.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Controller.h"


@implementation Controller

@synthesize model;

- (id)init {
    self = [super init];
    if (self) {
        self.model = [[Model alloc] init];
    }
    return self;
}

-(void)slideTile:(int)faceIndex From:(int)oldIndex To:(int)newIndex{
    //TODO this assumes that the tile at the old index is not empty and the tile at the new index is
    //this will be used to move the tiles when the user taps them
}

- (void)dealloc {
    [model dealloc];
    [super dealloc];
}

@end
