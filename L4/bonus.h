#ifndef BONUS_H
#define BONUS_H
#include "entity.h"
class bonus :
    public entity
{
public:
    static std::set<bonus*> exiting_bonuses;
    bonus(PAIR pos) :entity(pos, {0, -0.1}) {
        setRadius(5);
        exiting_bonuses.insert(this);
    }
    ~bonus() {
        exiting_bonuses.erase(this);
    }
    virtual void drawBonus() = 0;
    virtual void activate() = 0;
    virtual PAIR getSize();
    static void drawExitingBonuses();
    static void setRadius(double r);
    static void carriageHit();
    static void moveBonuses();
protected:
    static double radius;
};
#endif

