#ifndef CARRIAGE_SIZE_B_H
#define CARRIAGE_SIZE_B_H
#include "bonus.h"
class carriageSizeB :
    public bonus
{
public:
	carriageSizeB(PAIR pos) : bonus(pos) {};
	virtual void activate() override;
	virtual void drawBonus() override;
};
#endif
