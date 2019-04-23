//
// Created by 박현근 on 2019-04-22.
//

#include "BlockZ.h"

BlockZ::BlockZ() : Block(BLOCK_Z_MATRIX_SIZE, BlockType::Z) {
	Color color = WHITE;

	addBlockCell(0, 0, BlockCell{{0, 0}, color});
	addBlockCell(0, 1, BlockCell{{0, 0}, color});
	addBlockCell(1, 1, BlockCell{{0, 0}, color});
	addBlockCell(1, 2, BlockCell{{0, 0}, color});
}

BlockZ::~BlockZ() {

}
