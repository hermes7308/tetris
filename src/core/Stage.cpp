//
// Created by 박현근 on 2019-04-15.
//

#include <ncurses.h>
#include "Stage.h"


Stage::~Stage() {
	Stop();
}

void Stage::Start(StageContext *context) {
	// render fix
	while (isRunning) {
		// draw
		render(context);

		// input
		input(context);

		// physics
		physics(context);
	}
}

void Stage::Stop() {
	isRunning = false;
}

void Stage::render(StageContext *context) {
	clear();

	draw(context);

	refresh();
}