//
// Created by Lorenzo Ricci on 09/08/2020.
//

#ifndef UNTITLED_GAMECHARACTER_H
#define UNTITLED_GAMECHARACTER_H


#include "Subject.h"
#include <list>

class Gamecharacter: public Subject{
public:
    Gamecharacter(int x,int y);

    virtual ~Gamecharacter();

    int getPosX() const;

    void setPosX(int posX);

    int getPosY() const;

    void setPosY(int posY);

    void setPosition(int x,int y);

    void subscribe(Observer *o) override;

    void unsubscribe(Observer *o) override;

    void notify() override;

private:
    int posX;
    int posY;

    std::list<Observer*> observers;

};


#endif //UNTITLED_GAMECHARACTER_H
