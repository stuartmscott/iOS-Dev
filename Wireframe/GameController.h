//
//  GameController.h
//  Wireframe
//
//  Created by Kostadin on 12/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameModel.h"

@interface GameController : NSObject {
    
}
@property (retain) GameModel* model;
-(id)initWithModel:(GameModel*)m;
@end
