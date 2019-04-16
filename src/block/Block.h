//
// Created by 박현근 on 2019-04-15.
//
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

#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include <memory>
#include <vector>

using namespace std;

class Block {
public:
	virtual ~Block();

	struct Coordinate {
		int x;
		int y;
	};

	enum BlockType {
		I,
		J,
		L,
		O,
		S,
		T,
		Z
	};

	enum Degree {
		DEGREE_0 = 0,
		DEGREE_90,
		DEGREE_180,
		DEGREE_270,

		COUNT
	};
	unsigned int degree = DEGREE_0;

	Coordinate coordinate{};

	BlockType blockType{};

	int color{};

	vector<Block::Coordinate> getBlockCoordinates();

	void rotateClockwise();

	void rotateCounterClockwise();

protected:
	virtual Coordinate getBlock1() = 0;

	virtual Coordinate getBlock2() = 0;

	virtual Coordinate getBlock3() = 0;

	virtual Coordinate getBlock4() = 0;

};


#endif //TETRIS_BLOCK_H
