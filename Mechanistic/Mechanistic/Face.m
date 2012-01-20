//
//  Face.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Face.h"


@implementation Face

@synthesize tiles;

- (id)init {
    self = [super init];
    if (self) {
        //Creates a face
    }
    return self;
}

-(void)setEdgesN:(Edge*)north E:(Edge*)east S:(Edge*)south W:(Edge*)west{
    //sets up the neighbours
}

- (void)dealloc {
    [tiles release];
    [super dealloc];
}
@end