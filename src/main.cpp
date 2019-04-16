
#include <ncurses.h>
#include <iostream>
#include <vector>
#include "core/Stage.h"
#include "game/IntroStage.h"
#include "game/Tetris.h"

using namespace std;

void setup() {
	setlocale(LC_ALL, "");

	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);
}

void destroy() {
	endwin();
}

int main() {
	// setup
	setup();
	vector<Stage *> stages;
	stages.push_back(new IntroStage());
	stages.push_back(new Tetris());

	// intro
	auto *context = new StageContext();
	for (Stage *stage : stages) {
		if (context->status == StageContext::Status::STOP) {
			break;
		}

		stage->Start(context);
	}
	delete context;

	stages.clear();

	// destroy
	destroy();
}