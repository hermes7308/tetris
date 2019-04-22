//
// Created by 박현근 on 2019-04-22.
//

#ifndef TETRIS_BLOCKS_H
#define TETRIS_BLOCKS_H


#include "Block.h"

static const int BLOCK_S_MATRIX_SIZE = 3;

class BlockS : public Block {
public:
	BlockS();

	~BlockS();
};


#endif //TETRIS_BLOCKS_H
