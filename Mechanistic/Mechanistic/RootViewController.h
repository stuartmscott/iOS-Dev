//
//  RootViewController.h
//  Wireframe
//
//  Created by Kostadin on 19/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LevelSelection.h"

@interface RootViewController : UITableViewController {

}
@property (retain) NSArray* menuItems;
@property (nonatomic, retain) IBOutlet UIWindow *window;

@end
