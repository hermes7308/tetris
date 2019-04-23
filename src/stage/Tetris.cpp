//
// Created by 박현근 on 2019-04-23.
//

#include "Tetris.h"

Tetris::Tetris() = default;

Tetris::~Tetris() {
	destroy();
}

void Tetris::setup() const {
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
	init_pair(Block::RED, COLOR_RED, COLOR_BLACK);
	init_pair(Block::GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(Block::YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Block::BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(Block::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(Block::CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(Block::WHITE, COLOR_WHITE, COLOR_BLACK);
}

void Tetris::destroy() const { endwin(); }

void Tetris::Start() {
	setup();

	vector<Stage *> stages;
	stages.push_back(new IntroStage());
	stages.push_back(new GameStage());
	stages.push_back(new GameOverStage());

	auto *context = new StageContext();
	for (Stage *stage : stages) {
		if (context->status == StageContext::Status::STOP) {
			break;
		}

		stage->Start(context);
	}
	delete context;

	stages.clear();

	destroy();
}
