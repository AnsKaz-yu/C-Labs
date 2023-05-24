#ifndef GAME_H
#define GAME_H
#include "entity.h"
#include "carriage.h"
#include "ball.h"
#include "bonus.h"
class game
{
public:
	static game* G;
	int currentTime;
	game() {
		G = this;
		currentTime = 0;
		entity::initBonusesDuration();
		windowSize = { 500, 700 };
		//carriage* C = new carriage();
		create_field();
		ball* ballT = new ball();
		carriage* carriageT = new carriage();
	}
	PAIR getWindowSize();
	void initGame(int argc, char** argv);
	void mechanic();

	
private:
	PAIR windowSize;
	void initGlutFunctions();
	void create_field();
};
#endif

