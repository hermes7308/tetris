//
// Created by 박현근 on 2019-04-16.
//

#ifndef TETRIS_BLOCKL_H
#define TETRIS_BLOCKL_H


#include "Block.h"

class BlockL : public Block{
protected:
	Coordinate getBlock1() override;

	Coordinate getBlock2() override;

	Coordinate getBlock3() override;

	Coordinate getBlock4() override;

};


#endif //TETRIS_BLOCKL_H
