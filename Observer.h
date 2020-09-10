//
// Created by Lorenzo Ricci on 26/07/2020.
//

#ifndef UNTITLED_OBSERVER_H
#define UNTITLED_OBSERVER_H

//Interface
//Abstract class
class Observer
{
public:
    virtual ~Observer()= default;

    virtual void update()=0;
    virtual void attach()=0;
    virtual void detach()=0;
};
#endif //UNTITLED_OBSERVER_H
