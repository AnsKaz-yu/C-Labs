#ifndef BALL_H
#define BALL_H
#include "entity.h"
class ball :
    public entity
{
public:
    static ball* exiting_ball;
    bool sticking;
    bool protection;
    int changeSpeedT;

    ball() : entity({ 0.0, 0.0 }) {
        exiting_ball = this;
        sticking = true;
        protection = false;
        full_speed = 0.15;
        changeSpeedT = -1000000;
        radius = 10;
    }
    void bounceOffEntity(PAIR cont, entity* v);
    virtual void move() override;
    virtual PAIR getSize() override;
    void drawBall();
    ~ball() {
        exiting_ball = NULL;
    }
    
private:
    double radius;
    double full_speed;
};
#endif
