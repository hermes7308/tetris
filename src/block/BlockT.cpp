//
// Created by 박현근 on 2019-04-22.
//

#include "BlockT.h"

BlockT::BlockT() : Block(BLOCK_T_MATRIX_SIZE, BlockType::T) {
	Color color = CYAN;

	addBlockCell(0, 1, BlockCell{{0, 0}, color});
	addBlockCell(1, 0, BlockCell{{0, 0}, color});
	addBlockCell(1, 1, BlockCell{{0, 0}, color});
	addBlockCell(1, 2, BlockCell{{0, 0}, color});
}

BlockT::~BlockT() {

}
