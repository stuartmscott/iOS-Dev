//
//  Edge.m
//  Mechanistic
//
//  Created by Kostadin on 19/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "Edge.h"

@implementation Edge

@synthesize tiles;

- (id)init {
    self = [super init];
    if (self) {
        //Creates Edge
    }
    return self;
}

-(void)setFacesN:(Face*)north S:(Face*)south{
    //sets up the neighbours
}

@end
