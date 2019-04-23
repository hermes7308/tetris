//
// Created by 박현근 on 2019-04-22.
//

#include "BlockS.h"

BlockS::BlockS() : Block(BLOCK_S_MATRIX_SIZE, BlockType::S) {
	Color color = MAGENTA;

	addBlockCell(0, 1, BlockCell{{0, 0}, color});
	addBlockCell(0, 2, BlockCell{{0, 0}, color});
	addBlockCell(1, 0, BlockCell{{0, 0}, color});
	addBlockCell(1, 1, BlockCell{{0, 0}, color});
}

BlockS::~BlockS() {

}
