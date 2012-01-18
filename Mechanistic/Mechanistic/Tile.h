//
//  Tile.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Gear.h"

@interface Tile : NSObject

@property bool empty;
@property (retain) Gear *gear;

-(bool)hasGear;

@end
