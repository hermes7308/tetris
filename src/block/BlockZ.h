//
// Created by 박현근 on 2019-04-16.
//

#ifndef TETRIS_BLOCKZ_H
#define TETRIS_BLOCKZ_H


#include "Block.h"

class BlockZ : public Block{
protected:
	Coordinate getBlock1() override;

	Coordinate getBlock2() override;

	Coordinate getBlock3() override;

	Coordinate getBlock4() override;

};


#endif //TETRIS_BLOCKZ_H
