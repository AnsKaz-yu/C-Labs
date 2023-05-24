#ifndef CARRIAGE_H
#define CARRIAGE_H
#include "entity.h"
class carriage :
    public entity
{
public:
    static carriage* exiting_carriage;
    bool stickR;
    int changeSizeT;
    carriage() : entity({ 250, 100 }) {
        stickR = false;
        changeSizeT = -1000000;
        exiting_carriage = this;
        size = { 50, 10 };
        fullSpeed = 50;
    }
    void drawC();
    void moveLeft();
    void moveRight();
    virtual PAIR getSize();
    static void ballHit();
private:
    PAIR size;
    double fullSpeed;
};
#endif

