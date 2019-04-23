//
// Created by 박현근 on 2019-04-10.
//

#include "GameStage.h"

using namespace std;


GameStage::GameStage() {
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

GameStage::~GameStage() {
	delete currentBlock;

	blockQueue.clear();
}

void GameStage::drawStatic(StageContext *context) {
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

	// drawTetrisHoldBorderWindow
	tetrisHoldBorderWindow = newwin(TETRIS_HOLD_BORDER_HEIGHT, TETRIS_HOLD_BORDER_WIDTH, TETRIS_HOLD_BORDER_Y,
									TETRIS_HOLD_BORDER_X);
	refresh();

	box(tetrisHoldBorderWindow, 0, 0);
	mvwprintw(tetrisHoldBorderWindow, 0, 1, "Hold");
	wrefresh(tetrisHoldBorderWindow);

	// drawTetrisHoldWindow
	tetrisHoldWindow = newwin(TETRIS_HOLD_HEIGHT, TETRIS_HOLD_WIDTH, TETRIS_HOLD_Y, TETRIS_HOLD_X);
	refresh();

	// drawTetrisQueueBlockBorderWindow
	tetrisQueueBlockBorderWindow = newwin(TETRIS_QUEUE_BLOCK_BORDER_HEIGHT, TETRIS_QUEUE_BLOCK_BORDER_WIDTH,
										  TETRIS_QUEUE_BLOCK_BORDER_Y, TETRIS_QUEUE_BLOCK_BORDER_X);
	refresh();

	box(tetrisQueueBlockBorderWindow, 0, 0);
	mvwprintw(tetrisQueueBlockBorderWindow, 0, 1, "Next");
	wrefresh(tetrisQueueBlockBorderWindow);

	// drawTetrisQueueBlockWindow
	tetrisQueueBlockWindow = newwin(TETRIS_QUEUE_BLOCK_HEIGHT, TETRIS_QUEUE_BLOCK_WIDTH, TETRIS_QUEUE_BLOCK_Y,
									TETRIS_QUEUE_BLOCK_X);
	refresh();
}

void GameStage::draw(StageContext *context) {
	drawTetrisGame();

	drawHeldBlock();

	drawTempBlock();

	drawMetaInfo();
}

void GameStage::drawTetrisGame() {
	wclear(tetrisGameGroundWindow);
	drawStackedBlock();
	drawCurrentBlock();
	wrefresh(tetrisGameGroundWindow);
}

void GameStage::drawStackedBlock() {
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

void GameStage::drawCurrentBlock() {
	auto blockCells = currentBlock->getBlockCells();
	for (auto blockCell : blockCells) {
		wattron(tetrisGameGroundWindow, COLOR_PAIR(blockCell.color));
		mvwprintw(tetrisGameGroundWindow, blockCell.coordinate.y, blockCell.coordinate.x, "%s", BLOCK_CHARACTER);
		wattroff(tetrisGameGroundWindow, COLOR_PAIR(blockCell.color));
	}

	blockCells.clear();
}

void GameStage::drawHeldBlock() const {
	if (heldBlock != nullptr) {
		wclear(tetrisHoldWindow);

		auto blockCells = heldBlock->getPureBlockCells();
		for (auto blockCell : blockCells) {
			wattron(tetrisHoldWindow, COLOR_PAIR(blockCell.color));
			mvwprintw(tetrisHoldWindow, blockCell.coordinate.y, blockCell.coordinate.x, "%s", BLOCK_CHARACTER);
			wattroff(tetrisHoldWindow, COLOR_PAIR(blockCell.color));
		}

		blockCells.clear();
		wrefresh(tetrisHoldWindow);
	}
}

void GameStage::drawTempBlock() const {
	wclear(tetrisQueueBlockWindow);
	auto block = blockQueue.back();
	for (auto blockCell : block->getPureBlockCells()) {
		int y = blockCell.coordinate.y;
		int x = blockCell.coordinate.x;

		wattron(tetrisQueueBlockWindow, COLOR_PAIR(blockCell.color));
		mvwprintw(tetrisQueueBlockWindow, y, x, "%s", BLOCK_CHARACTER);
		wattroff(tetrisQueueBlockWindow, COLOR_PAIR(blockCell.color));
	}
	wrefresh(tetrisQueueBlockWindow);
}

void GameStage::drawMetaInfo() const {
	int y = 0;
	wclear(tetrisMetaInfoWindow);
	mvwprintw(tetrisMetaInfoWindow, y++, 0, "time : %ld", time(0));
	mvwprintw(tetrisMetaInfoWindow, y++, 0, "y : %d", currentBlock->getCurrentCoordinate().y);
	mvwprintw(tetrisMetaInfoWindow, y++, 0, "x : %d", currentBlock->getCurrentCoordinate().x);
	wrefresh(tetrisMetaInfoWindow);
}

void GameStage::input(StageContext *context) {
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
		case ' ':
			moveToDestination();
			return;
		case 'h':
		case 'H':
			holdBlock();
			return;
		default:
			break;
	}
}

GameStage::MoveStatus GameStage::moveToRight() {
	currentBlock->moveToRight();

	if (!isAllowedBlock()) {
		currentBlock->moveToLeft();
		return NOT_MOVED;
	}

	return MOVED;
}

GameStage::MoveStatus GameStage::moveToLeft() {
	currentBlock->moveToLeft();

	if (!isAllowedBlock()) {
		currentBlock->moveToRight();
		return NOT_MOVED;
	}

	return MOVED;
}

GameStage::MoveStatus GameStage::moveToDown() {
	currentBlock->moveToDown();

	if (!isAllowedBlock()) {
		currentBlock->moveToUp();

		stackBlock(currentBlock);
		loadNewBlock();

		if (!isAllowedBlock()) {
			// stage over;
			Stop();
			return NOT_MOVED;
		}

		addBlockToQueue();
		initGameTimer();

		return NOT_MOVED;
	}

	return MOVED;
}

void GameStage::moveToDestination() {
	while (MoveStatus::MOVED == moveToDown()) {

	}
}

void GameStage::rotateBlock() {
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

GameStage::RotateStatus GameStage::rotate() {
	currentBlock->rotateClockwise();

	if (!isAllowedBlock()) {
		currentBlock->rotateCounterClockwise();
		return NOT_ROTATED;
	}

	return ROTATED;
}

void GameStage::holdBlock() {
	if (heldBlock == nullptr) {
		heldBlock = currentBlock;
		loadNewBlock();
	} else {
		auto tempBlock = currentBlock;
		currentBlock = heldBlock;
		heldBlock = tempBlock;
	}

	if (!isAllowedBlock()) {
		holdBlock();
	}
}

void GameStage::physics(StageContext *context) {
	// remove full row
	removeFullRow();

	// stage timer
	milliseconds currentTime = getCurrentTime();
	unsigned int gameDelay = static_cast<unsigned int>((currentTime - beforeGameTime).count());
	if (gameDelay > (MAX_SPEED - speed)) {
		beforeGameTime = currentTime;
		moveToDown();
	}
}

void GameStage::removeFullRow() {
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

Block *GameStage::createBlock() {
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

void GameStage::addBlockToQueue() {
	Block *newBlock = createBlock();
	blockQueue.insert(blockQueue.begin(), newBlock);
}

Block *GameStage::getBlockFromQueue() {
	Block *newBlock = blockQueue.back();
	blockQueue.pop_back();

	return newBlock;
}

void GameStage::loadNewBlock() {
	currentBlock = getBlockFromQueue();
}

bool GameStage::isAllowedBlock() {
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

void GameStage::stackBlock(Block *block) {
	auto blockCells = block->getBlockCells();
	for (auto blockCell : blockCells) {
		stackedBlocks[blockCell.coordinate.y][blockCell.coordinate.x] = blockCell;
	}

	blockCells.clear();
//	delete currentBlock;
}

bool GameStage::isFullRow(int row) const {
	bool isFull = true;

	for (int col = 0; col < COLS; col++) {
		if (stackedBlocks[row][col].color == Block::Color::EMPTY) {
			isFull = false;
			break;
		}
	}

	return isFull;
}

void GameStage::setSpeed(int speed) {
	if (MAX_SPEED < speed) {
		this->speed = MAX_SPEED;
	}

	if (MIN_SPEED > speed) {
		this->speed = MIN_SPEED;
	}
}

void GameStage::initGameTimer() {
	beforeGameTime = getCurrentTime();
}
