//
// Created by 박현근 on 2019-04-19.
//

#include "Block.h"


Block::Block(unsigned int matrixSize, Block::BlockType blockType) : matrixSize(matrixSize),
																			 blockType(blockType) {
	matrix = new BlockCell *[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		matrix[i] = new BlockCell[matrixSize];
	}

	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			matrix[i][j] = {};
		}
	}

	int y = 0;
	int x = (10 - matrixSize) / 2;
	currentCoordinate = {y, x};
}

Block::~Block() {
	for (int i = 0; i < matrixSize; i++) {
		delete matrix[i];
	}

	delete[] matrix;
}

void Block::rotateClockwise() {
	int level = 0;
	int last = matrixSize - 1;
	int totNumOfLevels = matrixSize / 2;

	while (level < totNumOfLevels) {
		for (int i = level; i < last; i++) {
			swap(matrix[level][i], matrix[i][last]);
			swap(matrix[level][i], matrix[last][last - i + level]);
			swap(matrix[level][i], matrix[last - i + level][level]);
		}
		level++;
		last--;
	}
}

void Block::rotateCounterClockwise() {
	int level = 0;
	int last = matrixSize - 1;
	int totNumOfLevels = matrixSize / 2;

	while (level < totNumOfLevels) {
		for (int i = level; i < last; i++) {
			swap(matrix[level][i], matrix[last - i + level][level]);
			swap(matrix[level][i], matrix[last][last - i + level]);
			swap(matrix[level][i], matrix[i][last]);
		}
		level++;
		last--;
	}
}

void Block::swap(Block::BlockCell &blockCell1, Block::BlockCell &blockCell2) {
	BlockCell tempBlockCell = blockCell1;
	blockCell1 = blockCell2;
	blockCell2 = tempBlockCell;
}

void Block::moveToUp() {
	currentCoordinate.y--;
}

void Block::moveToDown() {
	currentCoordinate.y++;
}

void Block::moveToRight() {
	currentCoordinate.x++;
}

void Block::moveToLeft() {
	currentCoordinate.x--;
}

void Block::addBlockCell(int y, int x, Block::BlockCell blockCell) {
	if (y < 0 || y >= matrixSize) {
		return;
	}

	if (x < 0 || x >= matrixSize) {
		return;
	}

	matrix[y][x] = blockCell;
}

vector<Block::BlockCell> Block::getBlockCells() const {
	vector<BlockCell> blockCells;
	for (int y = 0; y < matrixSize; y++) {
		for (int x = 0; x < matrixSize; x++) {
			auto blockCell = matrix[y][x];
			if (blockCell.color != EMPTY) {
				blockCell.coordinate.y = currentCoordinate.y + y;
				blockCell.coordinate.x = currentCoordinate.x + x;
				blockCells.push_back(blockCell);
			}
		}
	}

	return blockCells;
}


unsigned int Block::getMatrixSize() const {
	return matrixSize;
}

Block::BlockCell **Block::getMatrix() const {
	return matrix;
}

const Block::Coordinate &Block::getCurrentCoordinate() const {
	return currentCoordinate;
}

Block::BlockType Block::getBlockType() const {
	return blockType;
}
