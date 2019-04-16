//
// Created by 박현근 on 2019-04-10.
//

#include <ncurses.h>
#include <random>
#include "Tetris.h"

using namespace std;

static const int UP = 65;
static const int DOWN = 66;
static const int RIGHT = 67;
static const int LEFT = 68;
static const int SPACE = 32;
static const int Z_UPPER = 90;
static const int Z_LOWER = 122;

const char *Tetris::BLOCK_CHARACTER = "■";

Tetris::Tetris() {
	srand(static_cast<unsigned int>(time(0)));

	// add bloc to block queue
	for (int i = 0; i < blockQueueSize; i++) {
		addBlockToQueue();
	}

	currentBlock = createBlock();
}

Tetris::~Tetris() {
	delete currentBlock;

	blockQueue.clear();
}

void Tetris::draw(StageContext *context) {
	drawBorder();
	drawStackedBlock();
	drawCurrentBlock();
	mvprintw(0, 0, "key : %d", key);
}

void Tetris::input(StageContext *context) {
	// Up, (27, 91, 65)
	// Down, (27, 91, 66)
	// Right, (27, 91, 67)
	// Left, (27, 91, 68)
	key = getch();
	if (key == 27) {
		key = getch();
		if (key == 91) {
			key = getch();
			switch (key) {
				case UP:
					moveToUp();
					return;
				case DOWN:
					moveToDown();
					return;
				case LEFT:
					moveToLeft();
					return;
				case RIGHT:
					moveToRight();
					return;
				default:
					return;
			}
		}
	}

	if (key == SPACE) {
		moveToDestination();
		return;
	}

	if (key == Z_UPPER || key == Z_LOWER) {
		rotate();
		return;
	}
}

void Tetris::physics(StageContext *context) {

}

void Tetris::drawBorder() {
	for (int row = 0; row < 22; row++) {
		for (int col = 0; col < 12; col++) {
			if (row == 0 || row == 21) {
				mvprintw(row + borderY, col + borderX, "%s", BLOCK_CHARACTER);
			}

			if (col == 0 || col == 11) {
				mvprintw(row + borderY, col + borderX, "%s", BLOCK_CHARACTER);
			}
		}
	}
}

void Tetris::drawStackedBlock() {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			int color = stackedBlocks[row][col];
			if (color != 0) {
				mvprintw(row + groundY, col + groundX, "%s", BLOCK_CHARACTER);
			}
		}
	}
}

void Tetris::drawCurrentBlock() {
	mvprintw(1, 0, "Degree: %d", currentBlock->degree);

	auto coordinates = currentBlock->getBlockCoordinates();
	for (Block::Coordinate coordinate : coordinates) {
		mvprintw(coordinate.y, coordinate.x, "%s", BLOCK_CHARACTER);
	}
	coordinates.clear();

	int count = 1;
	for (auto &block : blockQueue) {
		mvprintw(count, 30, "block index : %d, type : %d", count, block->blockType);
		count++;
	}
}

void Tetris::moveToUp() {
	currentBlock->coordinate.y--;
}

void Tetris::moveToRight() {
	currentBlock->coordinate.x++;
}

void Tetris::moveToLeft() {
	currentBlock->coordinate.x--;
}

void Tetris::moveToDown() {
	currentBlock->coordinate.y++;
}

void Tetris::moveToDestination() {
	currentBlock->coordinate.y = groundY + ROWS - 1;
}

void Tetris::rotate() {
	currentBlock->rotateClockwise();
}

Block *Tetris::createBlock() {
	int blockType = rand() % Block::BlockType::BLOCK_TYPE_COUNT;

	switch (blockType) {
		case Block::BlockType::I:
			return new BlockI(startX, startY);
		case Block::BlockType::J:
			return new BlockJ(startX, startY);
		case Block::BlockType::L:
			return new BlockL(startX, startY);
		case Block::BlockType::O:
			return new BlockO(startX, startY);
		case Block::BlockType::S:
			return new BlockS(startX, startY);
		case Block::BlockType::T:
			return new BlockT(startX, startY);
		case Block::BlockType::Z:
			return new BlockZ(startX, startY);
		default:
			return nullptr;
	}
}

void Tetris::addBlockToQueue() {
	Block *newBlock = createBlock();
	blockQueue.push_back(newBlock);
}
