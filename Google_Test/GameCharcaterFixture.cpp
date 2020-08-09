//
// Created by Lorenzo Ricci on 09/08/2020.
//

#include "gtest/gtest.h"
#include "../Gamecharacter.h"

class GameCharacterSuite : public ::testing::Test{

protected:
    virtual void SetUp()
    {
        c.setPosX(10);
        c.setPosY(10);
    }

    Gamecharacter c;
};

TEST_F(GameCharacterSuite, TestPosition)
{
    c.setPosition(6,8);

    ASSERT_EQ(6, c.getPosX());
    ASSERT_EQ(8, c.getPosY());
}

