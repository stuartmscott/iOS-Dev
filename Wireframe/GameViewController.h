//
//  GameViewController.h
//  Wireframe
//
//  Created by Kostadin on 12/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GameController.h"


@interface GameViewController : UIViewController {
    
}
@property (retain) GameController* controller;

- (id)initWithLevel:(int)level;

@end
