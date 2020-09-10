//
// Created by Lorenzo Ricci on 09/08/2020.
//

#ifndef UNTITLED_GAMECHARACTER_H
#define UNTITLED_GAMECHARACTER_H


#include "Subject.h"
#include <list>


//Concrete Subject
class Gamecharacter: public Subject{
public:
    //Constructor and Destructor
    Gamecharacter(int x=0,int y=0);
    virtual ~Gamecharacter();

    //Getter and Setter
    int getPosX() const;
    void setPosX(int posX);
    int getPosY() const;
    void setPosY(int posY);

    //Functions
    void setPosition(int x,int y);

    //Override Functions
    void subscribe(Observer *o) override;
    void unsubscribe(Observer *o) override;
    void notify() override;

private:
    int posX; //X position in the map of gamecharacter
    int posY; //Y position in the map of gamecharacter

    std::list<Observer*> observers;

};


#endif //UNTITLED_GAMECHARACTER_H
