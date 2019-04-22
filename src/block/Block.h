//
// Created by 박현근 on 2019-04-19.
//

#ifndef TETRIS_NEWBLOCK_H
#define TETRIS_NEWBLOCK_H

#include <vector>

using namespace std;

class Block {
public:
	struct Coordinate {
		int y = 0;
		int x = 0;
	};

	enum Color {
		EMPTY = 0, // black
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
		Color color = EMPTY;
	};

	enum BlockType {
		I = 0,
		J,
		L,
		O,
		S,
		T,
		Z,

		BLOCK_TYPE_COUNT
	};

protected:
	unsigned int matrixSize;

private:
	Coordinate currentCoordinate = {0, 0};

	BlockCell **matrix = nullptr;

	BlockType blockType;

public:
	Block(unsigned int matrixSize, BlockType blockType);

	~Block();

	void rotateClockwise();

	void rotateCounterClockwise();

	void swap(BlockCell &blockCell1, BlockCell &blockCell2);

	void moveToUp();

	void moveToDown();

	void moveToRight();

	void moveToLeft();

public:
	unsigned int getMatrixSize() const;

	BlockCell **getMatrix() const;

	const Coordinate &getCurrentCoordinate() const;

	vector<BlockCell> getBlockCells() const;

	BlockType getBlockType() const;

protected:
	void addBlockCell(int y, int x, BlockCell blockCell);
};

// BlockType
/**********/
// ####	, I
/**********/
// #
// ###	, J
/**********/
//   #
// ###	, L
/**********/
// ##
// ##	, O
/**********/
//  ##
// ##	, S
/**********/
//  #
// ###	, T
/**********/
// ##
//  ##	, Z
/**********/

#endif //TETRIS_NEWBLOCK_H
