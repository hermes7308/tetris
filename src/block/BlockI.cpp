//
// Created by 박현근 on 2019-04-22.
//

#include "BlockI.h"

BlockI::BlockI() : Block(BLOCK_I_MATRIX_SIZE, BlockType::I) {
	Color color = RED;

	int x = matrixSize / 2;
	for (int y = 0; y < matrixSize; y++) {
		addBlockCell(y, x, BlockCell{{0, 0}, color});
	}
}

BlockI::~BlockI() {
}
