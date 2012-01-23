//
//  MechanisticAppDelegate.h
//  Mechanistic
//
//  Created by Kostadin on 29/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RootViewController;

@interface MechanisticAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet RootViewController *viewController;

@end
