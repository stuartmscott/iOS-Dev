//
//  HighscoresViewController.m
//  Wireframe
//
//  Created by Kostadin on 19/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "HighscoresViewController.h"
#import "EngineUtils.h"
#import "OBJFileLoader.h"

@implementation HighscoresViewController

@synthesize table;
@synthesize selectionBar;
@synthesize byTimeItem;
@synthesize byMovesItem;
@synthesize tableItems;
@synthesize itemsByTime;
@synthesize itemsByMoves;
@synthesize levelNumber;

- (id)init {
    self = [super init];
    if (self) {
        // Nothing here
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
    //fil
    vector<string> lines;
    NSString *nsGearPath = [[NSBundle mainBundle] resourcePath];
    string directory = [nsGearPath cStringUsingEncoding:[NSString defaultCStringEncoding]];
    stringstream f;
    f << directory+"/highscores";
    f << levelNumber;
    f << ".txt";
    string fn = f.str();
    appendToStringVector(fn, lines);
    self.itemsByTime = [NSMutableArray arrayWithCapacity:lines.size()];
    self.itemsByMoves = [NSMutableArray arrayWithCapacity:lines.size()];
    for (int i=0; i<lines.size(); i++) {
        vector<string> tokens;
        split(lines.at(i).c_str(),' ',tokens);
        int time = atoi(tokens.at(1).c_str()) - atoi(tokens.at(0).c_str());;
        stringstream byTime;
        byTime<<i<<" "<<time;
        stringstream byMoves;
        byMoves<<i<<" "<<atoi(tokens.at(2).c_str());
        [self.itemsByTime addObject:[NSString stringWithCString:byTime.str().c_str() encoding:NSASCIIStringEncoding]];
        [self.itemsByMoves addObject:[NSString stringWithCString:byMoves.str().c_str() encoding:NSASCIIStringEncoding]];
        tokens.clear();
    }
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
        case 2:
            [self.view removeFromSuperview];
            break;
    }
}

@end
