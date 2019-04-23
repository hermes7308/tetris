//
// Created by 박현근 on 2019-04-22.
//

#include "BlockJ.h"

BlockJ::BlockJ() : Block(BLOCK_J_MATRIX_SIZE, BlockType::J) {
	Color color = GREEN;

	addBlockCell(0, 0, BlockCell{{0, 0}, color});
	addBlockCell(1, 0, BlockCell{{0, 0}, color});
	addBlockCell(1, 1, BlockCell{{0, 0}, color});
	addBlockCell(1, 2, BlockCell{{0, 0}, color});
}

BlockJ::~BlockJ() {

}
