//
// Created by 박현근 on 2019-04-23.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <ncurses.h>
#include <iostream>
#include <vector>
#include "../core/block/Block.h"
#include "../core/stage/Stage.h"
#include "IntroStage.h"
#include "GameOverStage.h"
#include "GameStage.h"

class Tetris {
public:
	Tetris();

	~Tetris();

	void Start();

	void setup() const;

	void destroy() const;
};


#endif //TETRIS_TETRIS_H
