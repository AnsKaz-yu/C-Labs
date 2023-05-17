#pragma once
#include "bomb.h"
class bonus :
    public box
{
public:
    virtual void draw(int x, int y, bool frame) final;
    virtual std::set<changing_box> activate(int x, int y) final;

private:
    int options[4][2] = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };
    void mixing();
};

