//
// Created by Lorenzo Ricci on 09/08/2020.
//

#ifndef UNTITLED_TILEMAP_H
#define UNTITLED_TILEMAP_H


#include "Observer.h"
#include "Gamecharacter.h"
#include <SFML/Graphics.hpp>


class TileMap: public Observer{
public:
    TileMap(Gamecharacter* g,sf::RenderWindow* window,int* tiles,int width,int height);

    virtual ~TileMap();

    //Getter and Setter
    int *getMap() const;

    void setMap(int *map);

    int getMWidth() const;

    void setMWidth(int mWidth);

    int getMHeight() const;

    void setMHeight(int mHeight);

    int getMX() const;

    void setMX(int mX);

    int getMY() const;

    void setMY(int mY);

    Gamecharacter *getGamecharacter() const;

    void setGamecharacter(Gamecharacter *gamecharacter);

    void draw();
    int getMapPos(int x,int y);

    const std::vector<std::vector<sf::RectangleShape>> &getTileMap() const;

    void update() override;
    void attach() override;
    void detach() override;

    std::vector<std::vector<sf::RectangleShape>> tileMap;
private:
    int* map;
    int m_width;
    int m_height;
    int m_x,m_y;
    Gamecharacter* gamecharacter;

    sf::RenderWindow* m_window;

};


#endif //UNTITLED_TILEMAP_H
