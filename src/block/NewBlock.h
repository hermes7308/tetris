//
// Created by 박현근 on 2019-04-19.
//

#ifndef TETRIS_NEWBLOCK_H
#define TETRIS_NEWBLOCK_H

#include <vector>

using namespace std;

class NewBlock {
public:
	struct Coordinate {
		int y = 0;
		int x = 0;
	};

	enum Color {
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE
	};

	struct BlockCell {
		Coordinate coordinate = {0, 0};
		Color color = BLACK;
	};

private:
	BlockCell **matrix;

	Coordinate coordinate;

	unsigned int matrixSize;

public:
	NewBlock(unsigned int matrixSize, vector<BlockCell> blockCells);

	~NewBlock();

	void rotateClockwise();

	void rotateCounterClockwise();

	void swap(BlockCell &blockCell1, BlockCell &blockCell2);

public:
	unsigned int getMatrixSize() const;

	BlockCell **getMatrix() const;

	const Coordinate &getCoordinate() const;

};


#endif //TETRIS_NEWBLOCK_H
