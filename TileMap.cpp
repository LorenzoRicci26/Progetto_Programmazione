//
// Created by Lorenzo Ricci on 09/08/2020.
//


#include "TileMap.h"

//Constructor and Destructor
TileMap::TileMap(Gamecharacter* g,sf::RenderWindow* window,int *tiles, int width, int height):gamecharacter(g),m_window(window),map(tiles),m_width(width),m_height(height)
{
    //Init TileMap
    tileMap.resize(this->m_width, std::vector<sf::RectangleShape>());

    for (std::size_t i = 0; i < this->m_width; i++) {
        tileMap[i].resize(this->m_width, sf::RectangleShape());
        for (std::size_t j = 0 ; j < this->m_height ; j++) {
            //tileMap
            tileMap[i][j].setSize(sf::Vector2f(32.f, 32.f));
            tileMap[i][j].setOutlineThickness(1.f);
            tileMap[i][j].setFillColor(sf::Color::White);
            tileMap[i][j].setOutlineColor(sf::Color::Black);
            tileMap[i][j].setPosition(i * 32.f, j * 32.f);
        }
    }
    attach();
}

TileMap::~TileMap()
{
    detach();
}

//Getter and Setter
const std::vector<std::vector<sf::RectangleShape>> &TileMap::getTileMap() const {
    return tileMap;
}

int *TileMap::getMap() const {
    return map;
}

void TileMap::setMap(int *m) {
    TileMap::map = m;
}

int TileMap::getMWidth() const {
    return m_width;
}

void TileMap::setMWidth(int mWidth) {
    m_width = mWidth;
}

int TileMap::getMHeight() const {
    return m_height;
}

void TileMap::setMHeight(int mHeight) {
    m_height = mHeight;
}

int TileMap::getMX() const {
    return m_x;
}

void TileMap::setMX(int mX) {
    m_x = mX;
}

int TileMap::getMY() const {
    return m_y;
}

void TileMap::setMY(int mY) {
    m_y = mY;
}

Gamecharacter *TileMap::getGamecharacter() const {
    return gamecharacter;
}

void TileMap::setGamecharacter(Gamecharacter *g) {
    this->gamecharacter = g;
}

//Functions
void TileMap::draw()
{
//Draw
    for (int i = 0; i < this->m_width; i++) {
        for (int j = 0; j < this->m_height; j++) {

            //Check if in (i,j) position there is  a wall
            if (getMapPos(i, j) == 9) {
                this->tileMap[i][j].setFillColor(sf::Color::Cyan);

            }

            //Check if (i,j) is the hero's node
            if (i == this->m_x && j == this->m_y) {
                this->tileMap[i][j].setFillColor(sf::Color::Green);
            }
            this->m_window->draw(this->tileMap[i][j]);
        }
    }
    this->m_window->display();
}

int TileMap::getMapPos(int x, int y) {
    if( x < 0 || x >= this->m_width || y < 0 || y >= this->m_height)
    {
        return 9;
    }
    return this->map[(y*this->m_width)+x];
}


//Override Functions
void TileMap::update()
{
    if(this->gamecharacter->getPosX() > this->m_width ||
       this->gamecharacter->getPosY() > this->m_height ||
       this->gamecharacter->getPosX() < 0 ||
       this->gamecharacter->getPosY() < 0 )
    {
        throw std::out_of_range ("Coords are unreachable");
    }
    this->m_x = gamecharacter->getPosX();
    this->m_y = gamecharacter->getPosY();
    draw();
}

void TileMap::attach()
{
    if(gamecharacter == nullptr){
        throw std::runtime_error("Gamecharacter passed in the constuctor is not initialized");
    }
    this->gamecharacter->subscribe(this);
}

void TileMap::detach()
{
    this->gamecharacter->unsubscribe(this);
}




