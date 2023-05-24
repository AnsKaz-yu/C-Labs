#ifndef BALL_PROTECT_B_H
#define _BALL_PROTECT_B_H
#include "bonus.h"
class ballProtectB:
	public bonus
{
public:
	ballProtectB(PAIR pos) : bonus(pos) {};
	virtual void activate() override;
	virtual void drawBonus() override;
};
#endif

