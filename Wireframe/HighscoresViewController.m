//
//  HighscoresViewController.m
//  Wireframe
//
//  Created by Kostadin on 19/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "HighscoresViewController.h"


@implementation HighscoresViewController

@synthesize table;
@synthesize selectionBar;
@synthesize byTimeItem;
@synthesize byMovesItem;
@synthesize tableItems;
@synthesize itemsByTime;
@synthesize itemsByMoves;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [table release];
    [tableItems release];
    [itemsByTime release];
    [itemsByMoves release];
    [selectionBar release];
    [byTimeItem release];
    [byMovesItem release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)showItemsByTime
{
    self.tableItems = itemsByTime;
    [table reloadData];
}

- (void)showItemsByMoves
{
    self.tableItems = itemsByMoves;
    [table reloadData];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.title = @"Highscores";
    self.itemsByTime = [NSArray arrayWithObjects:
     @"1. Kostadin 1:06:03",@"2. Stuart 1:07:01",nil];
    self.itemsByMoves = [NSArray arrayWithObjects:
                    @"1. Stuart 16",@"2. Kostadin 22",nil];
    [self.selectionBar setSelectedItem:byTimeItem];
    [self tabBar:selectionBar didSelectItem:byTimeItem];
}

- (void)viewDidUnload
{
    table = nil;
    tableItems = nil;
    itemsByTime = nil;
    itemsByMoves = nil;
    selectionBar = nil;
    [self setByTimeItem:nil];
    [self setByMovesItem:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [tableItems count];
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
    // Configure the cell.
    cell.textLabel.text = [tableItems objectAtIndex:indexPath.row];
    return cell;
}

- (void)tabBar:(UITabBar *)tabBar didSelectItem:(UITabBarItem *)item
{
    switch ([item tag]) {
        case 0:
            [self showItemsByTime];
            break;
        case 1:
            [self showItemsByMoves];
            break;
    }
}

@end
