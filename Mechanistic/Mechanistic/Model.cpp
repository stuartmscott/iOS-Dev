//
//  Model.m
//  Mechanistic
//
//  Created by Kostadin on 18/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Model.h"
#include <stdlib.h>

Tile** makeTiles(int num)
{
    Tile** tiles = (Tile**)malloc(sizeof(Tile)*num);
    for (int i=0;i<num;i++)
        tiles[i] = new Tile();
    return tiles;
}

Model::Model()
{
    //Top face
    Face *top = new Face(makeTiles(9));
        
    //Top edges
    Edge *te0 = new Edge(makeTiles(3));
    Edge *te1 = new Edge(makeTiles(3));
    Edge *te2 = new Edge(makeTiles(3));
    Edge *te3 = new Edge(makeTiles(3));
    
    //Side faces
    Face *sf0 = new Face(makeTiles(9));
    Face *sf1 = new Face(makeTiles(9));
    Face *sf2 = new Face(makeTiles(9));
    Face *sf3 = new Face(makeTiles(9));
    
    //Side edges
    Edge *se0 = new Edge(makeTiles(3));
    Edge *se1 = new Edge(makeTiles(3));
    Edge *se2 = new Edge(makeTiles(3));
    Edge *se3 = new Edge(makeTiles(3));
    
    //Bottom edges
    Edge *be0 = new Edge(makeTiles(3));
    Edge *be1 = new Edge(makeTiles(3));
    Edge *be2 = new Edge(makeTiles(3));
    Edge *be3 = new Edge(makeTiles(3));
    
    //Bottom face
    Face *bot = new Face(makeTiles(9));
    
    top->setEdges(te2, te1, te0, te3);
    
    te0->setFaces(top, sf0);
    te1->setFaces(top, sf1);
    te2->setFaces(top, sf2);
    te3->setFaces(top, sf3);
    
    sf0->setEdges(te0, se0, be0, se3);
    sf1->setEdges(te1, se1, be1, se0);
    sf2->setEdges(te2, se2, be2, se1);
    sf3->setEdges(te3, se3, be3, se2);
    
    se0->setFaces(sf1, sf0);
    se1->setFaces(sf2, sf1);
    se2->setFaces(sf3, sf2);
    se3->setFaces(sf0, sf3);
    
    te0->setFaces(sf0, bot);
    te1->setFaces(sf1, bot);
    te2->setFaces(sf2, bot);
    te3->setFaces(sf3, bot);
    
    bot->setEdges(te0, te1, te2, te3);
    
    faces[0] = top;
    faces[1] = sf0;
    faces[2] = sf1;
    faces[3] = sf2;
    faces[4] = sf3;
    faces[5] = bot;
    
    edges[0] = te0;
    edges[1] = te1;
    edges[2] = te2;
    edges[3] = te3;
    edges[4] = se0;
    edges[5] = se1;
    edges[6] = se2;
    edges[7] = se3;
    edges[8] = be0;
    edges[9] = be1;
    edges[10] = be2;
    edges[11] = be3;
        
    radius = 2.0f;//8.0
    theta = -1.5f;//-0.7
    phi = 0.5f;//0.5
}

Model::~Model()
{
    for (int i =0;i<6;i++)
    {
        delete faces[i];
    }
    for (int i =0;i<12;i++)
    {
        delete edges[i];
    }
}