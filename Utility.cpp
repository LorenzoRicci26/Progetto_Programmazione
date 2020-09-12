//
// Created by Lorenzo Ricci on 10/09/2020.
//

#include "Utility.h"

//Constructor and Destructor
Utility::Utility(int *tiles,int width,int height)
{
    this->map = tiles;

    this->m_width = width;

    this->m_height = height;

}

Utility::~Utility()=default;

//Getter and Setter

int *Utility::getMap() const {
    return map;
}

void Utility::setMap(int *_map) {
    Utility::map = _map;
}

int Utility::getMHeight() const {
    return m_height;
}

void Utility::setMHeight(int mHeight) {
    m_height = mHeight;
}

int Utility::getMWidth() const {
    return m_width;
}

void Utility::setMWidth(int mWidth) {
    m_width = mWidth;
}

//Functions
int Utility::GetMap(int _x, int _y)
{
    if( _x < 0 ||
        _x >= this->m_width ||
        _y < 0 ||
        _y >= this->m_height
            )
    {
        return 9;
    }
    return this->map[(_y*this->m_width)+_x];
}




