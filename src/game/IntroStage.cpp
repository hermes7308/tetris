//
// Created by 박현근 on 2019-04-10.
//

#include <ncurses.h>
#include "IntroStage.h"


void IntroStage::draw(StageContext *context) {
	int currentX = (WIDTH - TITLE_COLS) / 2;
	int currentY = 3;

	// TITLE
	for (int i = 0; i < TITLE_ROWS; i++) {
		mvprintw(currentY++, currentX, "%s", TITLE[i]);
	}

	// Author
	currentY++;
	mvprintw(currentY++, currentX + 40, "%s", AUTHOR);

	// start
	startX = currentX + 7;
	currentY += 5;
	startY = currentY;
	mvprintw(startY, startX + 2, "Start");
	exitY = ++currentY;
	mvprintw(exitY, startX + 2, "Exit");

	switch (currentCursor) {
		case START:
			mvprintw(startY, startX, "%s", CURSOR_CHARACTER);
			break;
		case EXIT:
			mvprintw(exitY, startX, "%s", CURSOR_CHARACTER);
			break;
		default:
			break;
	}
}

void IntroStage::input(StageContext *context) {
	// Up, (27, 91, 65)
	// Down, (27, 91, 66)
	key = getch();
	if (key == ERR) {
		return;
	}
	switch (key) {
		case UP:
			up();
			return;
		case DOWN:
			down();
			return;
	}

	// Enter, (10)
	if (key == 10) {
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