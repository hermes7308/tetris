//
// Created by 박현근 on 2019-04-15.
//

#include <vector>
#include "Block.h"

using namespace std;

vector<Block::Coordinate> Block::getBlockCoordinates() {
	vector<Block::Coordinate> coordinates;
	coordinates.push_back(getBlock1());
	coordinates.push_back(getBlock2());
	coordinates.push_back(getBlock3());
	coordinates.push_back(getBlock4());

	return coordinates;
}

void Block::rotateClockwise() {
	degree++;

	if (degree >= Block::Degree::COUNT) {
		degree = 0;
	}
}

void Block::rotateCounterClockwise() {
	degree--;

	if (degree < Block::DEGREE_0) {
		degree = Block::Degree::COUNT - 1;
	}
}

Block::~Block() {

}

