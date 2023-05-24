#ifndef BALL_SPEED_B_H
#define BALL_SPEED_B_H
#include "bonus.h"
class ballSpeedB :
    public bonus
{
public:
	ballSpeedB(PAIR pos) : bonus(pos) {};
	virtual void activate() override;
	virtual void drawBonus() override;
};
#endif

