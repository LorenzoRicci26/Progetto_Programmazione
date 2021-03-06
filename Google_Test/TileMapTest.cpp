//
// Created by Lorenzo Ricci on 10/08/2020.
//

#include "gtest/gtest.h"
#include "../TileMap.h"

int world_map[] =
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

TEST(TileMap , Constructor)
{
    auto * gamecharacter = new Gamecharacter;

    auto* utility = new Utility (world_map,20,20);

    sf::RenderWindow window (sf::VideoMode(640,640),"AstarSearch", sf::Style::Close | sf::Style::Titlebar | sf::Style ::Resize);

    gamecharacter->setPosX(10);
    gamecharacter->setPosY(10);

    TileMap map (gamecharacter,&window,utility);

    ASSERT_EQ(20, map.getMWidth());
    ASSERT_EQ(20, map.getMHeight());
    ASSERT_EQ(gamecharacter,map.getGamecharacter());

    ASSERT_EQ(10,map.getGamecharacter()->getPosX());
    ASSERT_EQ(10,map.getGamecharacter()->getPosY());

    for (int i = 0; i < map.getMWidth(); ++i)
    {
        for (int j = 0; j < map.getMHeight() ; ++j)
        {
            if (map.getMap()[i+ j * map.getMWidth()] == 1)
            {
                EXPECT_EQ(1 , map.getMap()[i + j * map.getMWidth()]);
            }

            if (map.getMap()[i+ j * map.getMWidth()] == 9)
            {
                EXPECT_EQ(9 , map.getMap()[i + j * map.getMWidth()]);
            }
        }
    }


}

TEST(TileMap, patternObserver)
{
    auto * gamecharacter = new Gamecharacter;

    auto* utility = new Utility (world_map,20,20);

    sf::RenderWindow window (sf::VideoMode(640,640),"AstarSearch", sf::Style::Close | sf::Style::Titlebar | sf::Style ::Resize);

    TileMap map(gamecharacter,&window,utility);

    ASSERT_NO_THROW(map.attach()); // Exception test

    gamecharacter->setPosition(1,1);

    ASSERT_EQ(1,map.getMX());
    ASSERT_EQ(1,map.getMY());

    ASSERT_THROW(gamecharacter->setPosition(-1,1),std::out_of_range); //Exception test
}

