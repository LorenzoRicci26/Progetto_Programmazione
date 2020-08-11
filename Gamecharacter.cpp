//
// Created by Lorenzo Ricci on 09/08/2020.
//

#include <stdexcept>
#include "Gamecharacter.h"

Gamecharacter::Gamecharacter(int x, int y):posX(x),posY(y){}

Gamecharacter::~Gamecharacter() {}

void Gamecharacter::subscribe(Observer *o)
{
    this->observers.push_back(o);
}

void Gamecharacter::unsubscribe(Observer *o)
{
    this->observers.remove(o);
}

void Gamecharacter::notify()
{
    for (auto observer : observers)
        observer->update();
}

int Gamecharacter::getPosX() const {
    return posX;
}

void Gamecharacter::setPosX(int posX) {
    this->posX = posX;
    notify();
}

int Gamecharacter::getPosY() const {
    return posY;
}

void Gamecharacter::setPosY(int posY) {
    this->posY = posY;
    notify();
}

void Gamecharacter::setPosition(int x ,int y)
{
    this->posX = x;
    this->posY = y;
    notify();
}

