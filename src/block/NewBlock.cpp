//
// Created by 박현근 on 2019-04-19.
//

#include "NewBlock.h"


NewBlock::NewBlock(unsigned int matrixSize, vector<NewBlock::BlockCell> blockCells) : matrixSize(matrixSize) {
	matrix = new BlockCell *[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		matrix[i] = new BlockCell[matrixSize];
	}

	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			matrix[i][j] = {};
		}
	}

	for (auto blockCell : blockCells) {
		int y = blockCell.coordinate.y;
		int x = blockCell.coordinate.x;

		if (y < 0 || y >= matrixSize) {
			continue;
		}

		if (x < 0 || x >= matrixSize) {
			continue;
		}

		matrix[y][x] = blockCell;
	}
}

NewBlock::~NewBlock() {
	for (int i = 0; i < matrixSize; i++) {
		delete matrix[i];
	}

	delete[] matrix;
}

void NewBlock::rotateClockwise() {
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

void NewBlock::rotateCounterClockwise() {
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

void NewBlock::swap(NewBlock::BlockCell &blockCell1, NewBlock::BlockCell &blockCell2) {
	BlockCell tempBlockCell = blockCell1;
	blockCell1 = blockCell2;
	blockCell2 = tempBlockCell;
}

unsigned int NewBlock::getMatrixSize() const {
	return matrixSize;
}

NewBlock::BlockCell **NewBlock::getMatrix() const {
	return matrix;
}

const NewBlock::Coordinate &NewBlock::getCoordinate() const {
	return coordinate;
}
