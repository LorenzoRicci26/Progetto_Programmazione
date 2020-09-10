//
// Created by Lorenzo Ricci on 09/08/2020.
//

#ifndef UNTITLED_TILEMAP_H
#define UNTITLED_TILEMAP_H


#include "Observer.h"
#include "Gamecharacter.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


//Concrete Observer
class TileMap: public Observer{
public:
    //Constructor and Destructor
    TileMap(Gamecharacter* g,sf::RenderWindow* window,int* tiles,int width=20,int height=20);
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

    //Functions
    void draw();
    int getMapPos(int x,int y);

    //Getter for the entire tilemap
    const std::vector<std::vector<sf::RectangleShape>> &getTileMap() const;

    //Override Functions
    void update() override;
    void attach() override;
    void detach() override;

    std::vector<std::vector<sf::RectangleShape>> tileMap; //public member tilemap

private:
    int* map;
    int m_width;
    int m_height;
    int m_x,m_y;
    Gamecharacter* gamecharacter;

    //SFML objects
    sf::RenderWindow* m_window;
};


#endif //UNTITLED_TILEMAP_H
