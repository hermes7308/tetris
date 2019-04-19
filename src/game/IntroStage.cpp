//
// Created by 박현근 on 2019-04-10.
//

#include <ncurses.h>
#include "IntroStage.h"

IntroStage::IntroStage() {
}

IntroStage::~IntroStage() {
}

void IntroStage::drawStatic(StageContext *context) {
	// TITLE
	drawTitle();

	// AUTHOR
	drawAuthor();

	// SELECT OPTION
	drawSelectOption();

	// SELECT OPTION CURSOR WINDOW
	drawSelectOptionCursorWindow();
}

void IntroStage::drawTitle() {
	titleWindow = newwin(TITLE_WINDOW_HEIGHT, TITLE_WINDOW_WIDTH, TITLE_Y, TITLE_X);
	refresh();

	box(titleWindow, 0, 0);
	for (int i = 0; i < TITLE_ROWS; i++) {
		mvwprintw(titleWindow, i + 1, 1, "%s", TITLE[i]);
	}
	wrefresh(titleWindow);
}

void IntroStage::drawAuthor() {
	authorWindow = newwin(AUTHOR_WINDOW_HEIGHT, AUTHOR_WINDOW_WIDTH, AUTHOR_Y, AUTHOR_X);
	refresh();

	mvwprintw(authorWindow, 0, 0, "%s", AUTHOR);
	wrefresh(authorWindow);
}

void IntroStage::drawSelectOption() {
	selectOptionWindow = newwin(SELECT_OPTION_HEIGHT, SELECT_OPTION_WIDTH, SELECT_OPTION_Y, SELECT_OPTION_X);
	refresh();

	for (int i = 0; i < COUNT; i++) {
		mvwprintw(selectOptionWindow, i, 0, SELECT_OPTIONS[i]);
	}
	wrefresh(selectOptionWindow);
}

void IntroStage::drawSelectOptionCursorWindow() {
	selectOptionCursorWindow = newwin(SELECT_OPTION_CURSOR_HEIGHT, SELECT_OPTION_CURSOR_WIDTH, SELECT_OPTION_CURSOR_Y,
									  SELECT_OPTION_CURSOR_X);
	refresh();
}

void IntroStage::draw(StageContext *context) {
	wclear(selectOptionCursorWindow);
	mvwprintw(selectOptionCursorWindow, currentCursor, 0, "%s", SELECT_OPTION_CURSOR_CHARACTER);
	wrefresh(selectOptionCursorWindow);
}

void IntroStage::input(StageContext *context) {
	key = getch();
	if (key == ERR) {
		return;
	}

	switch (key) {
		case KEY_UP:
			up();
			return;
		case KEY_DOWN:
			down();
			return;
		case 10:
			switch (currentCursor) {
				case Cursor::START:
					context->status = StageContext::CONTINUE;
					Stop();
					break;
				case Cursor::EXIT:
					context->status = StageContext::STOP;
					Stop();
					break;
				default:
					break;
			}
			return;;

		default:
			break;
	}
}

void IntroStage::physics(StageContext *context) {

}

void IntroStage::up() {
	currentCursor--;

	if (currentCursor < 0) {
		currentCursor = COUNT - 1;
	}
}

void IntroStage::down() {
	currentCursor++;

	if (currentCursor >= Cursor::COUNT) {
		currentCursor = 0;
	}
}