//
//  Tile.cpp
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Tile.h"


bool Tile::hasGear()
{
    return (gear!=NULL)?true:false;
}

Tile::~Tile()
{
    if (hasGear)
        delete gear;
 
}

