//
// Created by 박현근 on 2019-04-15.
//

#ifndef TETRIS_BLOCKI_H
#define TETRIS_BLOCKI_H

#include "./Block.h"

class BlockI : public Block {
public:
	BlockI(int x, int y) : Block({x, y}, Block::I, BlockColor::CYAN) {

	};

protected:
	Coordinate getBlock1() override;

	Coordinate getBlock2() override;

	Coordinate getBlock3() override;

	Coordinate getBlock4() override;
};


#endif //TETRIS_BLOCKI_H
