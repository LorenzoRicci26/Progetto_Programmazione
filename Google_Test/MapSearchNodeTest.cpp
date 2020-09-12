//
// Created by Lorenzo Ricci on 12/09/2020.
//

#include "gtest/gtest.h"
#include "../MapSearchNode.h"

int world_map0[] =
        {

// 0001020304050607080910111213141516171819
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 00
                1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
                1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 02
                1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 03
                1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 04
                1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 05
                1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 06
                1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,   // 07
                1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 08
                1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
                1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,   // 10
                1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,   // 11
                1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 12
                1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 13
                1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 14
                1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 15
                1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 16
                1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
                1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 18
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 19

        };

TEST(MapSearchNode, DefaultConstructor)
{
    MapSearchNode node;

    ASSERT_EQ(0,node.x);
    ASSERT_EQ(0,node.y);
}

TEST(MapSearchNode, Constructor)
{
    MapSearchNode node (5,8);

    ASSERT_EQ(5,node.x);
    ASSERT_EQ(8,node.y);
}

TEST(MapSearchNode, Functions)
{
    Utility utility(world_map0,20,20);

    AStarSearch<MapSearchNode> aStarSearch(&utility);

    MapSearchNode node;

    MapSearchNode next_node;

    next_node.x = 11;
    next_node.y = 3;

    MapSearchNode nodeGoal;

    nodeGoal.x = 12;
    nodeGoal.y = 3;

    ASSERT_EQ(15,node.GoalDistanceEstimate(nodeGoal));

    ASSERT_EQ(1,node.GetCost(&utility,next_node));

    ASSERT_TRUE(nodeGoal.IsSameState(nodeGoal));

    ASSERT_TRUE(node.GetSuccessors(&utility,&aStarSearch,&next_node));

    next_node.x = nodeGoal.x;
    next_node.y = nodeGoal.y;

    ASSERT_TRUE(next_node.IsGoal(nodeGoal));
}
