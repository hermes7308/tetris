//
// Created by 박현근 on 2019-04-22.
//

#include "BlockO.h"

BlockO::BlockO() : Block(BLOCK_O_MATRIX_SIZE, BlockType::O) {
	Color color = BLUE;

	addBlockCell(1, 1, BlockCell{{0, 0}, color});
	addBlockCell(1, 2, BlockCell{{0, 0}, color});
	addBlockCell(2, 1, BlockCell{{0, 0}, color});
	addBlockCell(2, 2, BlockCell{{0, 0}, color});
}

BlockO::~BlockO() {

}
