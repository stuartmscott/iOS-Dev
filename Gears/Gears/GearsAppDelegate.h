//
//  GearsAppDelegate.h
//  Gears
//
//  Created by Kostadin on 12/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GearsViewController;

@interface GearsAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet GearsViewController *viewController;

@end
