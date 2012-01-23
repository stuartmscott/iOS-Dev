//
//  LevelSelection.h
//  Wireframe
//
//  Created by Kostadin on 19/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HighscoresViewController.h"
#import "MechanisticViewController.h"

@interface LevelSelection : UITableViewController {
    
}

@property (retain) NSArray* tableItems;
@property BOOL forGame;
@property (nonatomic, retain) IBOutlet UIWindow *window;
@end
