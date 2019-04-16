//
// Created by 박현근 on 2019-04-16.
//

#ifndef TETRIS_BLOCKO_H
#define TETRIS_BLOCKO_H


#include "Block.h"

class BlockO : public Block {
public:
	BlockO(int x, int y) : Block({x, y}, Block::O, BlockColor::YELLOW) {

	};
protected:
	Coordinate getBlock1() override;

	Coordinate getBlock2() override;

	Coordinate getBlock3() override;

	Coordinate getBlock4() override;
};


#endif //TETRIS_BLOCKO_H
