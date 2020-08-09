//
// Created by Lorenzo Ricci on 09/08/2020.
//

#include "gtest/gtest.h"
#include "../Gamecharacter.h"

TEST(GameCharacter , DefaultConstrunctor)
{
    Gamecharacter c;

    ASSERT_EQ(0,c.getPosX());
    ASSERT_EQ(0,c.getPosY());
}


