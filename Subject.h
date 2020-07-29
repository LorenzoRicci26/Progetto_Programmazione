//
// Created by Lorenzo Ricci on 26/07/2020.
//

#ifndef UNTITLED_SUBJECT_H
#define UNTITLED_SUBJECT_H


#include "Observer.h"

class Subject
{
public:
    virtual ~Subject()=default;

    virtual void subscribe(Observer* o)=0;
    virtual void unsubscribe(Observer* o)=0;
    virtual void notify()=0;
};

#endif //UNTITLED_SUBJECT_H
