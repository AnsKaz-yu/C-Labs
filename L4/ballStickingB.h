#ifndef BALL_STICKING_B_H
#define BALL_STICKING_B_H
#include "bonus.h"
class ballStickingB :
    public bonus
{
public:
	ballStickingB(PAIR pos) : bonus(pos) {};
	virtual void activate() override;
	virtual void drawBonus() override;
};
#endif
