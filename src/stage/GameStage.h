//
// Created by 박현근 on 2019-04-10.
//

#ifndef TETRIS_GAMESTATE_H
#define TETRIS_GAMESTATE_H


#include <vector>
#include <ncurses.h>
#include <random>
#include <thread>
#include "../core/stage/Stage.h"
#include "../core/block/Block.h"
#include "../core/block/BlockI.h"
#include "../core/block/BlockJ.h"
#include "../core/block/BlockL.h"
#include "../core/block/BlockO.h"
#include "../core/block/BlockS.h"
#include "../core/block/BlockT.h"
#include "../core/block/BlockZ.h"

using namespace std;

static const char *const BLOCK_CHARACTER = "■";

class GameStage : public Stage {
public:
	GameStage();

	~GameStage();

	enum MoveStatus {
		NOT_MOVED,
		MOVED,
	};

	enum RotateStatus {
		NOT_ROTATED,
		ROTATED
	};

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

	const int TETRIS_META_INFO_BORDER_HEIGHT = 5;
	const int TETRIS_META_INFO_BORDER_WIDTH = 20;
	const int TETRIS_META_INFO_BORDER_Y = TETRIS_BORDER_Y + TETRIS_BORDER_HEIGHT - TETRIS_META_INFO_BORDER_HEIGHT;
	const int TETRIS_META_INFO_BORDER_X = TETRIS_BORDER_X - TETRIS_META_INFO_BORDER_WIDTH;
	WINDOW *tetrisMetaInfoBorderWindow;

	const int TETRIS_META_INFO_HEIGHT = TETRIS_META_INFO_BORDER_HEIGHT - 2;
	const int TETRIS_META_INFO_WIDTH = TETRIS_META_INFO_BORDER_WIDTH - 2;
	const int TETRIS_META_INFO_Y = TETRIS_META_INFO_BORDER_Y + 1;
	const int TETRIS_META_INFO_X = TETRIS_META_INFO_BORDER_X + 1;
	WINDOW *tetrisMetaInfoWindow;

	const int TETRIS_HOLD_BORDER_HEIGHT = 6;
	const int TETRIS_HOLD_BORDER_WIDTH = 6;
	const int TETRIS_HOLD_BORDER_Y = TETRIS_BORDER_Y;
	const int TETRIS_HOLD_BORDER_X = TETRIS_BORDER_X - TETRIS_HOLD_BORDER_WIDTH;
	WINDOW *tetrisHoldBorderWindow;

	const int TETRIS_HOLD_HEIGHT = 4;
	const int TETRIS_HOLD_WIDTH = 4;
	const int TETRIS_HOLD_Y = TETRIS_HOLD_BORDER_Y + 1;
	const int TETRIS_HOLD_X = TETRIS_HOLD_BORDER_X + 1;
	WINDOW *tetrisHoldWindow;

	const int TETRIS_QUEUE_BLOCK_BORDER_HEIGHT = 6;
	const int TETRIS_QUEUE_BLOCK_BORDER_WIDTH = 6;
	const int TETRIS_QUEUE_BLOCK_BORDER_Y = TETRIS_BORDER_Y;
	const int TETRIS_QUEUE_BLOCK_BORDER_X = TETRIS_BORDER_X + TETRIS_BORDER_WIDTH;
	WINDOW *tetrisQueueBlockBorderWindow;

	const int TETRIS_QUEUE_BLOCK_HEIGHT = TETRIS_QUEUE_BLOCK_BORDER_HEIGHT - 2;
	const int TETRIS_QUEUE_BLOCK_WIDTH = TETRIS_QUEUE_BLOCK_BORDER_HEIGHT - 2;
	const int TETRIS_QUEUE_BLOCK_Y = TETRIS_QUEUE_BLOCK_BORDER_Y + 1;
	const int TETRIS_QUEUE_BLOCK_X = TETRIS_QUEUE_BLOCK_BORDER_X + 1;
	WINDOW *tetrisQueueBlockWindow;

	Block *currentBlock = nullptr;

	Block *heldBlock = nullptr;

	// block queue
	const int blockQueueSize = 4;
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

	void drawHeldBlock() const;

	void drawTempBlock() const;

	void drawMetaInfo() const;

	// input event
	MoveStatus moveToRight();

	MoveStatus moveToLeft();

	MoveStatus moveToDown();

	void moveToDestination();

	void rotateBlock();

	RotateStatus rotate();

	void holdBlock();

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


#endif //TETRIS_GAMESTATE_H
