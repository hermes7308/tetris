//
// Created by 박현근 on 2019-04-10.
//

#ifndef TETRIS_INTROPAGE_H
#define TETRIS_INTROPAGE_H


static const int UP = 65;

static const int DOWN = 66;

#include "../model/PlayerCount.h"

class IntroPage {
public:
	PlayerCount Start();

	enum Cursor {
		ONE_PERSON = 0,
		TWO_PEOPLE,
		EXIT,

		COUNT
	};

private:
	PlayerCount playerCount = PlayerCount::NONE_SELECTED;

	int currentCursor = ONE_PERSON;

	void up();

	void down();

	void render();

	void input();

	void physics();
};


#endif //TETRIS_INTROPAGE_H
