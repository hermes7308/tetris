//
// Created by 박현근 on 2019-04-22.
//

#include "GameOverStage.h"

GameOverStage::GameOverStage() {
	setFrame(10);
}

GameOverStage::~GameOverStage() {

}

void GameOverStage::drawStatic(StageContext *context) {
	// title
	gameOverTitleWindow = newwin(GAME_OVER_WINDOW_HEIGHT, GAME_OVER_WINDOW_WIDTH, GAME_OVER_WINDOW_Y,
								 GAME_OVER_WINDOW_X);
	refresh();
	box(gameOverTitleWindow, 0, 0);
	for (int row = 0; row < TITLE_ROWS; row++) {
		mvwprintw(gameOverTitleWindow, row + 1, 1, "%s", TITTLE[row]);
	}
	wrefresh(gameOverTitleWindow);

	// gameOverExplanation
	gameOverExplanationWindow = newwin(GAME_OVER_EXPLANATION_HEIGHT, GAME_OVER_EXPLANATION_WIDTH,
									   GAME_OVER_EXPLANATION_Y, GAME_OVER_EXPLANATION_X);
	refresh();
}

void GameOverStage::draw(StageContext *context) {
	wclear(gameOverExplanationWindow);

	wattron(gameOverExplanationWindow, A_REVERSE);
	mvwprintw(gameOverExplanationWindow, 0, 0, GAME_OVER_EXPLANATION);
	wattroff(gameOverExplanationWindow, A_REVERSE);

	wrefresh(gameOverExplanationWindow);
}

void GameOverStage::input(StageContext *context) {
	key = getch();
	if (key == ERR) {
		return;
	}

	switch (key) {
		case 'q':
		case 'Q':
		case ESC:
			context->status = StageContext::STOP;
			Stop();
			return;
		case ' ':
			context->status = StageContext::CONTINUE;
			Stop();
			return;
		default:
			return;
	}
}

void GameOverStage::physics(StageContext *context) {

}
