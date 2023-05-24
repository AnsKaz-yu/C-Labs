#include "block.h"
#include "ball.h"
#include "ballProtectB.h"
#include "ballSpeedB.h"
#include "ballStickingB.h"
#include "carriageSizeB.h"
#include "game.h"
#include <GL/freeglut.h>

std::set<block*> block::existing_blocks;
PAIR block::size;
void block::ballHit() {
	block* to_delete = NULL;
	for (auto blockT : existing_blocks) {
		if (to_delete) {
			delete to_delete;
			to_delete = NULL;
		}
		PAIR c = contact(blockT, ball::exiting_ball);
		if (c != EMPTY_PAIR) {
			if (blockT->hp != absolut) blockT->hp--;
			ball::exiting_ball->bounceOffEntity(c, blockT);
			ball::exiting_ball->move();
		}
		if (blockT->hp <= 0) to_delete = blockT;
	}
	if (to_delete) {
		delete to_delete;
		to_delete = NULL;
	}
}
void block::blockHit() {
	for (auto block1 : existing_blocks) {
		for (auto block2 : existing_blocks) {
			PAIR c = contact(block1, block2);
			
			if (block1 != block2 && c!= EMPTY_PAIR) {
				block1->position.x -= block1->speed.x;
				block1->position.y -= block1->speed.y;
				block2->position.x -= block2->speed.x;
				block2->position.y -= block2->speed.y;
				block1->setSpeed({ block1->getSpeed().x * (-1), 0.0 });
				block2->setSpeed({ block1->getSpeed().x * (-1), 0.0 });
				while (c.x > 0) {
					block1->move();
					block2->move();
					c = contact(block1, block2);
					std::cout << c.x << '\n';
				}
				
			}
		}
	}
}

void block::moveBlocks() {
	for (auto blockT : existing_blocks) {
		blockT->move();
	}
}
void block::setSize(PAIR s) {
	size = s;
}

PAIR block::getSize() {
	return size;
}

void block::drawBlock() {
	glBegin(GL_QUADS);
	glColor3f(1.0 * hp / absolut * 0.6f, 1.0 * hp / absolut * 1.0f, 1.0 * hp / absolut * 0.8f);
	glVertex2f(position.x - size.x / 2, position.y - size.y / 2);
	glVertex2f(position.x - size.x / 2, position.y + size.y / 2);
	glVertex2f(position.x + size.x / 2, position.y + size.y / 2);
	glVertex2f(position.x + size.x / 2, position.y - size.y / 2);
	glEnd();
}

void block::drawExitingBlocks() {
	for (auto u : existing_blocks) {
		u->drawBlock();
	}
}

void block::create_bonus() {
	int chance = takeChance(4);
	bonus* p;
	switch (chance) {
	case 0:
		p = new ballProtectB(position);
		break;
	case 1:
		p = new ballSpeedB(position);
		break;
	case 2:
		p = new ballStickingB(position);
		break;
	case 3:
		p = new carriageSizeB(position);
		break;
	}
}

int block::getHP() {
	return hp;
}