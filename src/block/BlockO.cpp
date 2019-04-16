//
// Created by 박현근 on 2019-04-16.
//

#include "BlockO.h"

Block::Coordinate BlockO::getBlock1() {
	switch (degree) {
		case DEGREE_0:
			return Coordinate{coordinate.x, coordinate.y};
		case DEGREE_90:
			return Coordinate{coordinate.x + 1, coordinate.y};
		case DEGREE_180:
			return Coordinate{coordinate.x + 1, coordinate.y + 1};
		case DEGREE_270:
			return Coordinate{coordinate.x, coordinate.y + 1};
		default:
			return {};
	}
}

Block::Coordinate BlockO::getBlock2() {
	switch (degree) {
		case DEGREE_0:
			return Coordinate{coordinate.x + 1, coordinate.y};
		case DEGREE_90:
			return Coordinate{coordinate.x + 1, coordinate.y + 1};
		case DEGREE_180:
			return Coordinate{coordinate.x, coordinate.y + 1};
		case DEGREE_270:
			return Coordinate{coordinate.x, coordinate.y};
		default:
			return {};
	}
}

Block::Coordinate BlockO::getBlock3() {
	switch (degree) {
		case DEGREE_0:
			return Coordinate{coordinate.x + 1, coordinate.y + 1};
		case DEGREE_90:
			return Coordinate{coordinate.x, coordinate.y + 1};
		case DEGREE_180:
			return Coordinate{coordinate.x, coordinate.y};
		case DEGREE_270:
			return Coordinate{coordinate.x + 1, coordinate.y};
		default:
			return {};
	}
}

Block::Coordinate BlockO::getBlock4() {
	switch (degree) {
		case DEGREE_0:
			return Coordinate{coordinate.x, coordinate.y + 1};
		case DEGREE_90:
			return Coordinate{coordinate.x, coordinate.y};
		case DEGREE_180:
			return Coordinate{coordinate.x + 1, coordinate.y};
		case DEGREE_270:
			return Coordinate{coordinate.x + 1, coordinate.y + 1};
		default:
			return {};
	}
}