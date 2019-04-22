//
// Created by 박현근 on 2019-04-10.
//

#include "Tetris.h"

using namespace std;


const char *Tetris::BLOCK_CHARACTER = "■";

Tetris::Tetris() {
	srand(static_cast<unsigned int>(time(0)));

	// add bloc to block queue
	for (int i = 0; i < blockQueueSize + 1; i++) {
		addBlockToQueue();
	}
	loadNewBlock();

	// init gameTimer
	initGameTimer();

	setFrame(20);
}

Tetris::~Tetris() {
	delete currentBlock;

	blockQueue.clear();
}

void Tetris::drawStatic(StageContext *context) {
	clear();

	// drawTetrisBorder
	tetrisBorderWindow = newwin(TETRIS_BORDER_HEIGHT, TETRIS_BORDER_WIDTH, TETRIS_BORDER_Y, TETRIS_BORDER_X);
	refresh();

	box(tetrisBorderWindow, 0, 0);
	wrefresh(tetrisBorderWindow);

	// drawTetrisGameGroundWindow;
	tetrisGameGroundWindow = newwin(TETRIS_GAME_GROUND_HEIGHT, TETRIS_GAME_GROUND_WIDTH, TETRIS_GAME_GROUND_Y,
									TETRIS_GAME_GROUND_X);
	refresh();

	// drawTetrisMetaInfoBorderWindow
	tetrisMetaInfoBorderWindow = newwin(TETRIS_META_INFO_BORDER_HEIGHT, TETRIS_META_INFO_BORDER_WIDTH,
										TETRIS_META_INFO_BORDER_Y, TETRIS_META_INFO_BORDER_X);
	refresh();

	box(tetrisMetaInfoBorderWindow, 0, 0);
	wrefresh(tetrisMetaInfoBorderWindow);

	// drawTetrisMetaInfoWindow
	tetrisMetaInfoWindow = newwin(TETRIS_META_INFO_HEIGHT, TETRIS_META_INFO_WIDTH, TETRIS_META_INFO_Y,
								  TETRIS_META_INFO_X);
	refresh();
}

void Tetris::draw(StageContext *context) {
	drawTetrisGame();

	drawMetaInfo();
}

void Tetris::input(StageContext *context) {
	key = getch();
	if (key == ERR) {
		return;
	}

	switch (key) {
		case KEY_UP:
			rotateBlock();
			return;
		case KEY_DOWN:
			moveToDown();
			return;
		case KEY_LEFT:
			moveToLeft();
			return;
		case KEY_RIGHT:
			moveToRight();
			return;
	}

	if (key == ' ') {
		moveToDestination();
		return;
	}
}

void Tetris::physics(StageContext *context) {
	// remove full row
	removeFullRow();

	// game timer
	milliseconds currentTime = getCurrentTime();
	unsigned int gameDelay = static_cast<unsigned int>((currentTime - beforeGameTime).count());
	if (gameDelay > (MAX_SPEED - speed)) {
		beforeGameTime = currentTime;
		moveToDown();
	}
}

void Tetris::drawTetrisGame() {
	wclear(tetrisGameGroundWindow);
	drawStackedBlock();
	drawCurrentBlock();
	wrefresh(tetrisGameGroundWindow);
}

void Tetris::drawStackedBlock() {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			auto blockCell = stackedBlocks[row][col];
			if (blockCell.color != Block::Color::EMPTY) {
				wattron(tetrisGameGroundWindow, COLOR_PAIR(blockCell.color));
				mvwprintw(tetrisGameGroundWindow, row, col, "%s", BLOCK_CHARACTER);
				wattroff(tetrisGameGroundWindow, COLOR_PAIR(blockCell.color));
			}
		}
	}
}

void Tetris::drawCurrentBlock() {
	auto blockCells = currentBlock->getBlockCells();
	for (auto blockCell : blockCells) {
		wattron(tetrisGameGroundWindow, COLOR_PAIR(blockCell.color));
		mvwprintw(tetrisGameGroundWindow, blockCell.coordinate.y, blockCell.coordinate.x, "%s", BLOCK_CHARACTER);
		wattroff(tetrisGameGroundWindow, COLOR_PAIR(blockCell.color));
	}

	blockCells.clear();
}

void Tetris::drawMetaInfo() const {
	int y = 0;
	wclear(tetrisMetaInfoWindow);
	mvwprintw(tetrisMetaInfoWindow, y++, 0, "time : %ld", time(0));
	mvwprintw(tetrisMetaInfoWindow, y++, 0, "y : %d", currentBlock->getCurrentCoordinate().y);
	mvwprintw(tetrisMetaInfoWindow, y++, 0, "x : %d", currentBlock->getCurrentCoordinate().x);

	mvwprintw(tetrisMetaInfoWindow, y++, 0, "BlockType : %d", currentBlock->getBlockType());


	auto matrix = currentBlock->getMatrix();
	for (int row = 0; row < currentBlock->getMatrixSize(); row++) {
		for (int col = 0; col < currentBlock->getMatrixSize(); col++) {
			if (matrix[row][col].color == Block::Color::EMPTY) {
				mvwprintw(tetrisMetaInfoWindow, y, col * 2, "0");
			} else {
				mvwprintw(tetrisMetaInfoWindow, y, col * 2, "1");
			}
		}
		y++;
	}

	wrefresh(tetrisMetaInfoWindow);
}

Tetris::MoveStatus Tetris::moveToRight() {
	currentBlock->moveToRight();

	if (!isAllowedBlock()) {
		currentBlock->moveToLeft();
		return NOT_MOVED;
	}

	return MOVED;
}

Tetris::MoveStatus Tetris::moveToLeft() {
	currentBlock->moveToLeft();

	if (!isAllowedBlock()) {
		currentBlock->moveToRight();
		return NOT_MOVED;
	}

	return MOVED;
}

Tetris::MoveStatus Tetris::moveToDown() {
	currentBlock->moveToDown();

	if (!isAllowedBlock()) {
		currentBlock->moveToUp();

		stackBlock(currentBlock);
		loadNewBlock();
		addBlockToQueue();
		initGameTimer();

		return NOT_MOVED;
	}

	return MOVED;
}

void Tetris::moveToDestination() {
	while (MoveStatus::MOVED == moveToDown()) {

	}
}

void Tetris::rotateBlock() {
	if (ROTATED == rotate()) {
		return;
	}

	// move left
	if (MOVED == moveToLeft()) {
		if (ROTATED == rotate()) {
			return;
		}
		moveToRight();
	}

	// move right
	if (MOVED == moveToRight()) {
		if (ROTATED == rotate()) {
			return;
		}
		moveToLeft();
	}

	if (Block::BlockType::I == currentBlock->getBlockType()) {
		if (MOVED == moveToLeft()) {
			if (MOVED == moveToLeft()) {
				if (ROTATED == rotate()) {
					return;
				}
				moveToRight();
			}
			moveToRight();
		}

		if (MOVED == moveToRight()) {
			if (MOVED == moveToRight()) {
				if (ROTATED == rotate()) {
					return;
				}
				moveToLeft();
			}
			moveToLeft();
		}
	}
}

Tetris::RotateStatus Tetris::rotate() {
	currentBlock->rotateClockwise();

	if (!isAllowedBlock()) {
		currentBlock->rotateCounterClockwise();
		return NOT_ROTATED;
	}

	return ROTATED;
}

void Tetris::removeFullRow() {
	for (int row = 0; row < ROWS; row++) {
		if (isFullRow(row)) {
			for (int index = row; index > 0; index--) {
				for (int col = 0; col < COLS; col++) {
					stackedBlocks[index][col] = stackedBlocks[index - 1][col];
					stackedBlocks[index - 1][col] = Block::BlockCell{};
				}
			}
		}
	}
}

Block *Tetris::createBlock() {
	int blockType = rand() % Block::BlockType::BLOCK_TYPE_COUNT;

	switch (blockType) {
		case Block::BlockType::I:
			return new BlockI();
		case Block::BlockType::J:
			return new BlockJ();
		case Block::BlockType::L:
			return new BlockL();
		case Block::BlockType::O:
			return new BlockO();
		case Block::BlockType::S:
			return new BlockS();
		case Block::BlockType::T:
			return new BlockT();
		case Block::BlockType::Z:
			return new BlockZ();
		default:
			return nullptr;
	}
}

void Tetris::addBlockToQueue() {
	Block *newBlock = createBlock();
	blockQueue.insert(blockQueue.begin(), newBlock);
}

Block *Tetris::getBlockFromQueue() {
	Block *newBlock = blockQueue.back();
	blockQueue.pop_back();

	return newBlock;
}

void Tetris::loadNewBlock() {
	currentBlock = getBlockFromQueue();
}

bool Tetris::isAllowedBlock() {
	auto blockCells = currentBlock->getBlockCells();

	for (auto blockCell : blockCells) {
		int y = blockCell.coordinate.y;
		if (y < 0 || y >= ROWS) {
			return false;
		}

		int x = blockCell.coordinate.x;
		if (x < 0 || x >= COLS) {
			return false;
		}

		if (stackedBlocks[y][x].color != Block::Color::EMPTY) {
			return false;
		}
	}

	return true;
}

void Tetris::stackBlock(Block *block) {
	auto blockCells = block->getBlockCells();
	for (auto blockCell : blockCells) {
		stackedBlocks[blockCell.coordinate.y][blockCell.coordinate.x] = blockCell;
	}

	blockCells.clear();
//	delete currentBlock;
}

bool Tetris::isFullRow(int row) const {
	bool isFull = true;

	for (int col = 0; col < COLS; col++) {
		if (stackedBlocks[row][col].color == Block::Color::EMPTY) {
			isFull = false;
			break;
		}
	}

	return isFull;
}

void Tetris::setSpeed(int speed) {
	if (MAX_SPEED < speed) {
		this->speed = MAX_SPEED;
	}

	if (MIN_SPEED > speed) {
		this->speed = MIN_SPEED;
	}
}

void Tetris::initGameTimer() { beforeGameTime = getCurrentTime(); }
