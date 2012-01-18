//
//  Controller.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Model.h"

@interface Controller : NSObject

@property (retain) Model *model;

-(void)slideTile:(int)faceIndex From:(int) oldIndex To:(int) newIndex;

@end
