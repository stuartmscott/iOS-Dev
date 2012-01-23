//
//  HighscoresViewController.h
//  Wireframe
//
//  Created by Kostadin on 19/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface HighscoresViewController : UIViewController {
    
}
@property (retain) NSMutableArray* itemsByTime;
@property (retain) NSMutableArray* itemsByMoves;
@property (retain) NSArray* tableItems;
@property (retain,nonatomic) IBOutlet UITableView* table;
@property (nonatomic, retain) IBOutlet UITabBar *selectionBar;
@property (nonatomic, retain) IBOutlet UITabBarItem *byTimeItem;
@property (nonatomic, retain) IBOutlet UITabBarItem *byMovesItem;
@property int levelNumber;

- (void)tabBar:(UITabBar *)tabBar didSelectItem:(UITabBarItem *)item;

@end
