//
//  Converter.cpp
//  Mechanistic
//
//  Created by Kostadin on 21/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Converter.h"
#include "OBJFileLoader.h"
#include "TransformNode.h"
#include "LightNode.h"
#define TC_TO_TC_ON_FACE 20.4f
#define SCALE_FACTOR 0.02f
#define LIFT_GEAR 3.2f
#define FACE_DISTANCE_FROM_ORIGIN 45.02498f
#define EDGE_DISTANCE_FROM_ORIGIN 53.474935f


Converter::Converter(string &directory)
{
    gear = new MeshNode();
    string gfn = directory+"/Gear.obj";
    loadMesh(gfn, gear, false);
    gear->material->setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
    faceTile = new MeshNode();
    string tfn = directory+"/FacePrism.obj";
    loadMesh(tfn, faceTile, false);
    faceTile->material->setAmbient(0.84f, 0.65f, 0.43f, 1.0f);
    edgeTile = new MeshNode();
    string efn = directory+"/EdgePrism.obj";
    loadMesh(efn, edgeTile, false);
    edgeTile->material->setAmbient(0.84f, 0.65f, 0.43f, 1.0f);
}

Converter::~Converter()
{
    delete gear;
    delete faceTile;
    delete edgeTile;
}

SceneGraphNode* Converter::makeTile(Tile* tileRef, bool isEdge)
{
    SceneGraphNode* tileGroup = new SceneGraphNode();
    if (!tileRef->empty)
    {
        if (tileRef->hasGear)
        {
            Transform* rotate = new Transform(ROTATE, tileRef->gear->rotation, 0.0f, 1.0f, 0.0f);
            Transform* translate = new Transform(TRANSLATE, 0.0f, LIFT_GEAR, 0.0f);
            TransformNode* positionGear = new TransformNode(rotate, translate);
            positionGear->getChildren()->push_back(gear);
            tileGroup->getChildren()->push_back(positionGear);
        }
        if(isEdge)
            tileGroup->getChildren()->push_back(edgeTile);
        else
            tileGroup->getChildren()->push_back(faceTile);
    }
    return tileGroup;
}

SceneGraphNode* Converter::makeFace(Face* faceRef)
{
    SceneGraphNode* faceGroup = new SceneGraphNode();
    for(int i=0; i<9; i++)
    {
        SceneGraphNode* tileGroup = makeTile(faceRef->tiles[i], false);
        TransformNode* positionTileGroup = new TransformNode(TRANSLATE, ((i%3)-1.0f)*TC_TO_TC_ON_FACE, 0.0f, ((i/3)-1.0f)*TC_TO_TC_ON_FACE);
        positionTileGroup->getChildren()->push_back(tileGroup);
        faceGroup->getChildren()->push_back(positionTileGroup);
    }
    return faceGroup;
}

SceneGraphNode* Converter::makeEdge(Edge* edgeRef)
{
    SceneGraphNode* edgeGroup = new SceneGraphNode();
    for(int i=0; i<3; i++)
    {
        SceneGraphNode* tileGroup = makeTile(edgeRef->tiles[i], true);
        TransformNode* positionTileGroup = new TransformNode(TRANSLATE, ((i%3)-1.0f)*TC_TO_TC_ON_FACE, 0.0f, 0.0f);
        positionTileGroup->getChildren()->push_back(tileGroup);
        edgeGroup->getChildren()->push_back(positionTileGroup);
    }
    return edgeGroup;
}

SceneGraphNode* Converter::convert(Model *m)
{
    SceneGraphNode* root = new SceneGraphNode();
    TransformNode* scaleEverything = new TransformNode(SCALE, SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);
    //Faces
    SceneGraphNode* faceTop = makeFace(m->faces[0]);
    SceneGraphNode* faceSide1 = makeFace(m->faces[1]);
    SceneGraphNode* faceSide2 = makeFace(m->faces[2]);
    SceneGraphNode* faceSide3 = makeFace(m->faces[3]);
    SceneGraphNode* faceSide4 = makeFace(m->faces[4]);
    SceneGraphNode* faceBottom = makeFace(m->faces[5]);
    //Top face
    TransformNode* positionFaceTop = new TransformNode(TRANSLATE, 0.0f, FACE_DISTANCE_FROM_ORIGIN, 0.0f);
    positionFaceTop->getChildren()->push_back(faceTop);
    scaleEverything->getChildren()->push_back(positionFaceTop);
    //Side face 1
    TransformNode* positionFaceSide1 = new TransformNode(new Transform(TRANSLATE, 0.0f, FACE_DISTANCE_FROM_ORIGIN, 0.0f),new Transform(ROTATE, 90.0f, 1.0f, 0.0f, 0.0f));
    positionFaceSide1->getChildren()->push_back(faceSide1);
    scaleEverything->getChildren()->push_back(positionFaceSide1);
    //Side face 2
    TransformNode* positionFaceSide2 = new TransformNode(new Transform(TRANSLATE, 0.0f, FACE_DISTANCE_FROM_ORIGIN, 0.0f),new Transform(ROTATE, -90.0f, 0.0f, 0.0f, 1.0f), new Transform(ROTATE, 90.0f, 1.0f, 0.0f, 0.0f));
    positionFaceSide2->getChildren()->push_back(faceSide2);
    scaleEverything->getChildren()->push_back(positionFaceSide2);
    //Side face 3
    TransformNode* positionFaceSide3 = new TransformNode(new Transform(TRANSLATE, 0.0f, FACE_DISTANCE_FROM_ORIGIN, 0.0f),new Transform(ROTATE, 180.0f, 0.0f, 0.0f, 1.0f), new Transform(ROTATE, 90.0f, 1.0f, 0.0f, 0.0f));
    positionFaceSide3->getChildren()->push_back(faceSide3);
    scaleEverything->getChildren()->push_back(positionFaceSide3);
    //Side face 4
    TransformNode* positionFaceSide4 = new TransformNode(new Transform(TRANSLATE, 0.0f, FACE_DISTANCE_FROM_ORIGIN, 0.0f),new Transform(ROTATE, 90.0f, 0.0f, 0.0f, 1.0f), new Transform(ROTATE, 90.0f, 1.0f, 0.0f, 0.0f));
    positionFaceSide4->getChildren()->push_back(faceSide4);
    scaleEverything->getChildren()->push_back(positionFaceSide4);
    //Bottom face
    TransformNode* positionFaceBottom = new TransformNode(new Transform(TRANSLATE, 0.0f, FACE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, 180.0f, 0.0f, 0.0f, 1.0f));
    positionFaceBottom->getChildren()->push_back(faceBottom);
    scaleEverything->getChildren()->push_back(positionFaceBottom);
    //Edges
    SceneGraphNode* edge0 = makeEdge(m->edges[0]);
    SceneGraphNode* edge1 = makeEdge(m->edges[1]);
    SceneGraphNode* edge2 = makeEdge(m->edges[2]);
    SceneGraphNode* edge3 = makeEdge(m->edges[3]);
    SceneGraphNode* edge4 = makeEdge(m->edges[4]);
    SceneGraphNode* edge5 = makeEdge(m->edges[5]);
    SceneGraphNode* edge6 = makeEdge(m->edges[6]);
    SceneGraphNode* edge7 = makeEdge(m->edges[7]);
    SceneGraphNode* edge8 = makeEdge(m->edges[8]);
    SceneGraphNode* edge9 = makeEdge(m->edges[9]);
    SceneGraphNode* edge10 = makeEdge(m->edges[10]);
    SceneGraphNode* edge11 = makeEdge(m->edges[11]);
    //Edge 0
    TransformNode* positionEdge0 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, 45.0f, 1.0f, 0.0f, 0.0f));
    positionEdge0->getChildren()->push_back(edge0);
    scaleEverything->getChildren()->push_back(positionEdge0);
    /*
    //Edge 1
    TransformNode* positionEdge1 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, 45.0f, 1.0f, 0.0f, 0.0f), new Transform(ROTATE, -90.0f, 0.0f, 1.0f, 0.0f));
    positionEdge1->getChildren()->push_back(edge1);
     scaleEverything->getChildren()->push_back(positionEdge1);
    */
    //Edge 2
    TransformNode* positionEdge2 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, 45.0f, 1.0f, 0.0f, 0.0f), new Transform(ROTATE, 180.0f, 0.0f, 1.0f, 0.0f));
    positionEdge2->getChildren()->push_back(edge2);
    scaleEverything->getChildren()->push_back(positionEdge2);
    /*
    //Edge 3
    TransformNode* positionEdge3 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, -45.0f, 1.0f, 0.0f, 0.0f));
    positionEdge3->getChildren()->push_back(edge3);
    scaleEverything->getChildren()->push_back(positionEdge3);
     */
    
    //Edge 4
    TransformNode* positionEdge4 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, -90.0f, 0.0f, 0.0f, 1.0f), new Transform(ROTATE, -45.0f, 0.0f, 1.0f, 0.0f));
    positionEdge4->getChildren()->push_back(edge4);
    scaleEverything->getChildren()->push_back(positionEdge4);
    //Edge 5
    TransformNode* positionEdge5 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, -90.0f, 0.0f, 0.0f, 1.0f), new Transform(ROTATE, 45.0f, 0.0f, 1.0f, 0.0f));
    positionEdge5->getChildren()->push_back(edge5);
    scaleEverything->getChildren()->push_back(positionEdge5);
    //Edge 6
    TransformNode* positionEdge6 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, -90.0f, 0.0f, 0.0f, 1.0f), new Transform(ROTATE, 135.0f, 0.0f, 1.0f, 0.0f));
    positionEdge6->getChildren()->push_back(edge6);
    scaleEverything->getChildren()->push_back(positionEdge6);
    //Edge 7
    TransformNode* positionEdge7 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, -90.0f, 0.0f, 0.0f, 1.0f), new Transform(ROTATE, -135.0f, 0.0f, 1.0f, 0.0f));
    positionEdge7->getChildren()->push_back(edge7);
    scaleEverything->getChildren()->push_back(positionEdge7);
     
    //Edge 8
    TransformNode* positionEdge8 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, 135.0f, 1.0f, 0.0f, 0.0f));
    positionEdge8->getChildren()->push_back(edge8);
    scaleEverything->getChildren()->push_back(positionEdge8);
    /*
    //Edge 9
    TransformNode* positionEdge9 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, 135.0f, 1.0f, 0.0f, 0.0f), new Transform(ROTATE, 90.0f, 0.0f, 1.0f, 0.0f));
    positionEdge9->getChildren()->push_back(edge9);
    scaleEverything->getChildren()->push_back(positionEdge9);
     */
    //Edge 10
    TransformNode* positionEdge10 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, -135.0f, 1.0f, 0.0f, 0.0f));
    positionEdge10->getChildren()->push_back(edge10);
    scaleEverything->getChildren()->push_back(positionEdge10);
    /*
    //Edge 11
    TransformNode* positionEdge11 = new TransformNode(new Transform(TRANSLATE, 0.0f, EDGE_DISTANCE_FROM_ORIGIN, 0.0f), new Transform(ROTATE, 135.0f, 1.0f, 0.0f, 0.0f), new Transform(ROTATE, -90.0f, 0.0f, 1.0f, 0.0f));
    positionEdge11->getChildren()->push_back(edge11);
    scaleEverything->getChildren()->push_back(positionEdge11);
     */
    
    root->getChildren()->push_back(scaleEverything);
    return root;
}