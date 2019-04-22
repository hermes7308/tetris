
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
	timeout(TRUE);
	keypad(stdscr, TRUE);
	cbreak();
	curs_set(0);

	// init color
	start_color();
	init_pair(Block::Color::RED, COLOR_RED, COLOR_BLACK);
	init_pair(Block::Color::GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(Block::Color::YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Block::Color::BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(Block::Color::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(Block::Color::CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(Block::Color::WHITE, COLOR_WHITE, COLOR_BLACK);
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