#ifndef BLOCK_H
#define BLOCK_H
#include "entity.h"
#define absolut 5
class block :
    public entity
{
public:
    static std::set<block*> existing_blocks;
    block(PAIR pos) : entity(pos) {
        size = { 50, 25 };
        int ch = takeChance(10);
        if (ch == 1) { //the case of creating a moving block
            setSpeed({ 0.05, 0.0 });
        }
        hp = takeChance(absolut) + 1;
        existing_blocks.insert(this);
    }
    ~block() {
        existing_blocks.erase(this);
        create_bonus();
    }
    static void moveBlocks();
    static void ballHit();
    static void blockHit();
    static void setSize(PAIR s);
    static void drawExitingBlocks();
    void drawBlock();
    virtual PAIR getSize() override;
    int getHP();
private:
    int hp;
    void create_bonus();
    static PAIR size;
};
#endif
