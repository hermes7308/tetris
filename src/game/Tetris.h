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

	enum RotateStatus {
		NOT_ROTATED,
		ROTATED
	};

	Tetris();

	virtual ~Tetris();

protected:
	void drawStatic(StageContext *context) override;

	void draw(StageContext *context) override;

	void input(StageContext *context) override;

	void physics(StageContext *context) override;

private:
	static const int ROWS = 20;
	static const int COLS = 10;

	Block::BlockCell stackedBlocks[ROWS][COLS];

	// draw
	// border
	const int TETRIS_BORDER_HEIGHT = ROWS + 2;
	const int TETRIS_BORDER_WIDTH = COLS + 2;
	const int TETRIS_BORDER_Y = 0;
	const int TETRIS_BORDER_X = (WIDTH - TETRIS_BORDER_WIDTH) / 2;
	WINDOW *tetrisBorderWindow;

	const int TETRIS_GAME_GROUND_HEIGHT = ROWS;
	const int TETRIS_GAME_GROUND_WIDTH = COLS;
	const int TETRIS_GAME_GROUND_Y = TETRIS_BORDER_Y + 1;
	const int TETRIS_GAME_GROUND_X = TETRIS_BORDER_X + 1;
	WINDOW *tetrisGameGroundWindow;

	const int TETRIS_META_INFO_BORDER_HEIGHT = 20;
	const int TETRIS_META_INFO_BORDER_WIDTH = 30;
	const int TETRIS_META_INFO_BORDER_Y = TETRIS_BORDER_Y;
	const int TETRIS_META_INFO_BORDER_X = TETRIS_BORDER_X + TETRIS_BORDER_WIDTH + 1;
	WINDOW *tetrisMetaInfoBorderWindow;

	const int TETRIS_META_INFO_HEIGHT = TETRIS_META_INFO_BORDER_HEIGHT - 2;
	const int TETRIS_META_INFO_WIDTH = TETRIS_META_INFO_BORDER_WIDTH - 2;
	const int TETRIS_META_INFO_Y = TETRIS_META_INFO_BORDER_Y + 1;
	const int TETRIS_META_INFO_X = TETRIS_BORDER_X + TETRIS_BORDER_WIDTH + 1 + 1;
	WINDOW *tetrisMetaInfoWindow;

	// start
	const int startX = (COLS / 2);
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

	milliseconds beforeGameTime;

	int speed = MIN_SPEED;

	// draw
	void drawTetrisGame();

	void drawStackedBlock();

	void drawCurrentBlock();

	void drawMetaInfo() const;

	// input event
	MoveStatus moveToRight();

	MoveStatus moveToLeft();

	MoveStatus moveToDown();

	void moveToDestination();

	void rotateBlock();

	RotateStatus rotate();

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

	void initGameTimer();
};


#endif //TETRIS_TETRIS_H
