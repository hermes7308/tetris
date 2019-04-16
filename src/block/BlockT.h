//
// Created by 박현근 on 2019-04-16.
//

#ifndef TETRIS_BLOCKT_H
#define TETRIS_BLOCKT_H


#include "Block.h"

class BlockT : public Block {
public:
	BlockT() : Block({0, 0}, Block::T, BlockColor::MAGENTA) {

	};
protected:
	Coordinate getBlock1() override;

	Coordinate getBlock2() override;

	Coordinate getBlock3() override;

	Coordinate getBlock4() override;

};


#endif //TETRIS_BLOCKT_H
