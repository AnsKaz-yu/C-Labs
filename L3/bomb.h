#pragma once
#include "box.h"
class bomb :
    public box
{
public:
    bomb() :radius(create_rand(5) + 1) {};
    virtual void draw(int x, int y, bool frame) final;
    virtual std::set<changing_box> activate(int x, int y) final;
private:
    int radius;
};

