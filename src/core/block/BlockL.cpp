//
// Created by 박현근 on 2019-04-22.
//

#include "BlockL.h"

BlockL::BlockL() : Block(BLOCK_L_MATRIX_SIZE, BlockType::L) {
	Color color = YELLOW;

	addBlockCell(0, 2, BlockCell{{0, 0}, color});
	addBlockCell(1, 0, BlockCell{{0, 0}, color});
	addBlockCell(1, 1, BlockCell{{0, 0}, color});
	addBlockCell(1, 2, BlockCell{{0, 0}, color});
}

BlockL::~BlockL() {

}
