//
//  GameController.m
//  Wireframe
//
//  Created by Kostadin on 12/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "GameController.h"


@implementation GameController

@synthesize model;

-(id)initWithModel:(GameModel*)m
{
    self = [super init];
    if (self) {
        self.model = m;
    }
    return self;
}

- (void)dealloc {
    [model dealloc];
    [super dealloc];
}

@end
