//
// Created by Lorenzo Ricci on 10/09/2020.
//

#ifndef UNTITLED_MAPSEARCHNODE_H
#define UNTITLED_MAPSEARCHNODE_H

#include "stlastar.h" // See header for copyright and usage information

class Utility;

class MapSearchNode {
public:
    int x;	 // the (x,y) positions of the node
    int y;

    MapSearchNode(){ x = y = 0; }
    MapSearchNode( int px, int py ) { x=px; y=py; }

    float GoalDistanceEstimate( MapSearchNode &nodeGoal );
    bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors(Utility* u, AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
    float GetCost(Utility* u, MapSearchNode &successor );
    bool IsSameState( MapSearchNode &rhs );

    void PrintNodeInfo();
};


#endif //UNTITLED_MAPSEARCHNODE_H
