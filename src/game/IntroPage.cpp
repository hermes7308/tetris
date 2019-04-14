//
// Created by 박현근 on 2019-04-10.
//

#include <ncurses.h>
#include "IntroPage.h"


IntroPageResult IntroPage::Start() {
	this->renderStaticView();

	while (this->result == IntroPageResult::NONE_SELECTED) {
		// render
		render();

		// input
		input();

		// physics
		physics();

	}

	return result;
}

void IntroPage::renderStaticView() {
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
}

void IntroPage::render() {
	switch (currentCursor) {
		case START:
			mvprintw(exitY, startX, "%s", CURSOR_SPACE);
			mvprintw(startY, startX, "%s", CURSOR_CHARECTOR);
			break;
		case EXIT:
			mvprintw(startY, startX, "%s", CURSOR_SPACE);
			mvprintw(exitY, startX, "%s", CURSOR_CHARECTOR);
			break;
		default:
			break;
	}
}

void IntroPage::input() {
	// Up, (27, 91, 65)
	// Down, (27, 91, 66)
	key = getch();
	if (key == 27) {
		key = getch();
		if (key == 91) {
			key = getch();
			switch (key) {
				case UP:
					up();
					break;
				case DOWN:
					down();
					break;
				default:
					break;
			}
		}
	}

	// Enter, (10)
	if (key == 10) {
		switch (currentCursor) {
			case Cursor::START:
				result = IntroPageResult::START;
				break;
			case Cursor::EXIT:
				result = IntroPageResult::EXIT;
				break;
			default:
				break;
		}
	}
}

void IntroPage::physics() {
}

void IntroPage::up() {
	currentCursor--;

	if (currentCursor < 0) {
		currentCursor = COUNT - 1;
	}
}

void IntroPage::down() {
	currentCursor++;

	if (currentCursor >= Cursor::COUNT) {
		currentCursor = 0;
	}
}
