//
//  GameModel.m
//  Wireframe
//
//  Created by Kostadin on 12/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "GameModel.h"


@implementation GameModel
@synthesize level;
- (id)initWithLevel:(int)l
{
    self = [super init];
    if (self) {
        self.level = l;
    }
    return self;
}
@end
