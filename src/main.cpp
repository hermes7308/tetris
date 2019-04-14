
#include <ncurses.h>
#include <iostream>
#include "game/IntroPage.h"

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

	// intro
	// player one, player two
	auto *introPage = new IntroPage();
	IntroPage::Cursor result = introPage->Start();

	delete introPage;

	switch (result) {
		case IntroPage::START:
			mvprintw(0, 0, "Start Tetris");
			break;
		case IntroPage::EXIT:
			break;
		default:
			break;
	}

	// destroy
	destroy();
}