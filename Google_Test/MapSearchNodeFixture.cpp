//
// Created by Lorenzo Ricci on 09/08/2020.
//

#include "gtest/gtest.h"
#include "../findpath.cpp"



class MapSearchNodeSuite : public ::testing::Test{

protected:
    virtual void SetUp(){
        m_start.x = 10;
        m_start.y = 10;
        m_goal.x = 0;
        m_goal.y = 19;
    }

    MapSearchNode m_start;
    MapSearchNode m_goal;
};

TEST_F(MapSearchNodeSuite, TestGoalDistanceEstimate)
{
    ASSERT_EQ(19,m_start.GoalDistanceEstimate(m_goal));
}

TEST_F(MapSearchNodeSuite, TestIsGoal)
{
    ASSERT_TRUE(m_start.IsGoal(m_goal));
}

