//
// Created by 박현근 on 2019-04-10.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H


#include "../core/Stage.h"
#include "../block/Block.h"
#include "../block/BlockI.h"
#include <queue>

class Tetris : public Stage {
public:
	static const char *BLOCK_CHARACTER;

	Tetris();

protected:
	void draw(StageContext *context) override;

	void input(StageContext *context) override;

	void physics(StageContext *context) override;

private:
	static const int ROWS = 20;
	static const int COLS = 10;

	int stackedBlocks[ROWS][COLS];

	// draw
	// block
	const int borderX = 0;
	const int borderY = 2;
	// ground
	const int groundX = borderX + 1;
	const int groundY = borderY + 1;
	// start
	const int startX = groundX + 4;
	const int startY = groundY + 2;

	Block *currentBlock = new BlockI();

	// block queue
	const int blockQueueSize = 5;
	queue<Block> blockQueue;

	// input value
	int key{};

	// draw
	void drawBorder();

	void drawStackedBlock();

	void drawCurrentBlock();

	// input event
	void moveToUp();

	void moveToRight();

	void moveToLeft();

	void moveToDown();

	void moveToDestination();

	void rotate();
};


#endif //TETRIS_TETRIS_H
