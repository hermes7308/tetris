//
// Created by 박현근 on 2019-04-16.
//

#ifndef TETRIS_BLOCKS_H
#define TETRIS_BLOCKS_H


#include "Block.h"

class BlockS : public Block {
protected:
	Coordinate getBlock1() override;

	Coordinate getBlock2() override;

	Coordinate getBlock3() override;

	Coordinate getBlock4() override;

};


#endif //TETRIS_BLOCKS_H
