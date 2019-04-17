//
// Created by 박현근 on 2019-04-10.
//

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

	// init gameTimer
	beforeGameTime = getCurrentMilliseconds();
}

Tetris::~Tetris() {
	delete currentBlock;

	blockQueue.clear();
}

void Tetris::draw(StageContext *context) {
	drawBorder();
	drawStackedBlock();
	drawCurrentBlock();

	drawMetaInfo();
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
	// remove full row
	removeFullRow();

	// game timer
	unsigned int gameDelay = static_cast<unsigned int>((currentTime - beforeGameTime).count());
	if (gameDelay > (MAX_SPEED - speed)) {
		beforeGameTime = currentTime;
		moveToDown();
	}
}

void Tetris::removeFullRow() {
	for (int row = 0; row < ROWS; row++) {
		if (isFullRow(row)) {
			for (int index = row; index > 0; index--) {
				for (int col = 0; col < COLS; col++) {
					stackedBlocks[index][col] = stackedBlocks[index - 1][col];
					stackedBlocks[index - 1][col] = 0;
				}
			}
		}
	}
}

bool Tetris::isFullRow(int row) const {
	bool isFull = true;

	for (int col = 0; col < COLS; col++) {
		if (stackedBlocks[row][col] == 0) {
			isFull = false;
			break;
		}
	}
	return isFull;
}

void Tetris::drawBorder() {
	drawBasket(borderX, borderY, 12, 22);
}

void Tetris::drawBasket(int x, int y, int width, int height) const {
	// draw left & right line
	for (int row = 0; row < height - 1; row++) {
		mvaddch(y + row, x, ACS_VLINE);
		mvaddch(y + row, x + width - 1, ACS_VLINE);
	}

	// draw top & under line
	for (int col = 1; col < width - 1; col++) {
		mvaddch(y + height - 1, x + col, ACS_HLINE);
	}

	// draw corners line
	mvaddch(y + height - 1, x, ACS_LLCORNER);
	mvaddch(y + height - 1, x + width - 1, ACS_LRCORNER);
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
	auto coordinates = currentBlock->getBlockCoordinates();
	for (Block::Coordinate coordinate : coordinates) {
		mvprintw(groundY + coordinate.y, groundX + coordinate.x, "%s", BLOCK_CHARACTER);
	}
	coordinates.clear();
}

void Tetris::drawMetaInfo() const {
	int x = 14;
	int y = 1;

	drawRect(x++, y++, 20, 4);

	mvprintw(y++, x, "Degree: %d", currentBlock->degree);
	mvprintw(y++, x, "time : %ld", time(0));
}

void Tetris::drawRect(int x, int y, int width, int height) const {
	// draw left & right line
	for (int row = 1; row < height - 1; row++) {
		mvaddch(y + row, x, ACS_VLINE);
		mvaddch(y + row, x + width - 1, ACS_VLINE);
	}

	// draw top & under line
	for (int col = 1; col < width - 1; col++) {
		mvaddch(y, x + col, ACS_HLINE);
		mvaddch(y + height - 1, x + col, ACS_HLINE);
	}

	// draw corners line
	mvaddch(y, x, ACS_ULCORNER);
	mvaddch(y, x + width - 1, ACS_URCORNER);

	mvaddch(y + height - 1, x, ACS_LLCORNER);
	mvaddch(y + height - 1, x + width - 1, ACS_LRCORNER);
}

Tetris::MoveStatus Tetris::moveToUp() {
	currentBlock->coordinate.y--;

	if (!isAllowedBlock()) {
		currentBlock->coordinate.y++;
		return NOT_MOVED;
	}

	return MOVED;
}

Tetris::MoveStatus Tetris::moveToRight() {
	currentBlock->coordinate.x++;

	if (!isAllowedBlock()) {
		currentBlock->coordinate.x--;
		return NOT_MOVED;
	}

	return MOVED;
}

Tetris::MoveStatus Tetris::moveToLeft() {
	currentBlock->coordinate.x--;

	if (!isAllowedBlock()) {
		currentBlock->coordinate.x++;
		return NOT_MOVED;
	}

	return MOVED;
}

Tetris::MoveStatus Tetris::moveToDown() {
	currentBlock->coordinate.y++;

	if (!isAllowedBlock()) {
		currentBlock->coordinate.y--;

		stackBlock(currentBlock);
		loadNewBlock();
		addBlockToQueue();

		return MOVED;
	}

	return NOT_MOVED;
}

void Tetris::moveToDestination() {
	while (MoveStatus::NOT_MOVED == moveToDown()) {

	}
}

void Tetris::rotate() {
	currentBlock->rotateClockwise();

	if (!isAllowedBlock()) {
		currentBlock->rotateCounterClockwise();
	}
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
	vector<Block::Coordinate> coordinates = currentBlock->getBlockCoordinates();

	for (auto &coordinate : coordinates) {

		int x = coordinate.x;
		if (x < 0 || x >= COLS) {
			return false;
		}

		int y = coordinate.y;
		if (y < 0 || y >= ROWS) {
			return false;
		}

		if (stackedBlocks[y][x] != 0) {
			return false;
		}
	}

	return true;
}

void Tetris::stackBlock(Block *block) {
	auto coordinates = block->getBlockCoordinates();
	for (auto coordinate : coordinates) {
		stackedBlocks[coordinate.y][coordinate.x] = block->color;
	}
	delete block;
}

void Tetris::setSpeed(int speed) {
	if (MAX_SPEED < speed) {
		this->speed = MAX_SPEED;
	}

	if (MIN_SPEED > speed) {
		this->speed = MIN_SPEED;
	}
}
