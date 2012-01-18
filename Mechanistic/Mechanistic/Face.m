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

- (void)dealloc {
    [tiles dealloc];
    [super dealloc];
}
@end