//
// Created by Lorenzo Ricci on 10/08/2020.
//


#include "gtest/gtest.h"
#include "../TileMap.h"


class TileMapSuite : public ::testing::Test{

protected:
    void SetUp()
    {
        map.setMWidth(10);
        map.setMHeight(10);
        map.setGamecharacter(c);
        map.setMap(world_map);
        map.setMX(0);
        map.setMY(0);
    }

    TileMap map;
    Gamecharacter* c;
    int* world_map;
    sf::RenderWindow* window;
};