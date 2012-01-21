//
//  Tile.h
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "Gear.h"

class Tile 
{
public:
    bool empty;
    Gear *gear;
    bool hasGear();
    ~Tile();
};