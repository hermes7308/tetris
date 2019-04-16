//
// Created by 박현근 on 2019-04-10.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H


#include <vector>
#include <ncurses.h>
#include <random>
#include <thread>
#include "../core/Stage.h"
#include "../block/Block.h"
#include "../block/BlockI.h"
#include "../block/BlockJ.h"
#include "../block/BlockL.h"
#include "../block/BlockO.h"
#include "../block/BlockS.h"
#include "../block/BlockT.h"
#include "../block/BlockZ.h"

using namespace std;

class Tetris : public Stage {
public:
	static const char *BLOCK_CHARACTER;

	enum MoveStatus {
		NOT_MOVED,
		MOVED,
	};

	Tetris();

	virtual ~Tetris();

	MoveStatus moveToDown();

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
	const int startX = groundX + 3;
	const int startY = 1;

	Block *currentBlock = nullptr;

	// block queue
	const int blockQueueSize = 5;
	vector<Block *> blockQueue;

	// input value
	int key{};

	// gameTimer
	const int MAX_SPEED = 1000;
	const int MIN_SPEED = 100;

	thread gameTimerThread;
	int speed = MIN_SPEED;
	bool isRunning = true;

	// draw
	void drawBorder();

	void drawStackedBlock();

	void drawCurrentBlock();

	// input event
	MoveStatus moveToUp();

	MoveStatus moveToRight();

	MoveStatus moveToLeft();

	void moveToDestination();

	void rotate();

	// block queue
	Block *createBlock();

	void addBlockToQueue();

	Block *getBlockFromQueue();

	void loadNewBlock();

	bool isAllowedBlock();

	void stackBlock(Block *block);

	void removeFullRow();

	bool isFullRow(int row) const;

	// gameTimer
	void setSpeed(int speed);

	void drawMetaInfo() const;
};


#endif //TETRIS_TETRIS_H
