//
// Created by 박현근 on 2019-04-10.
//

#include <ncurses.h>
#include "IntroPage.h"

int key;

PlayerCount IntroPage::Start() {
	while (playerCount == PlayerCount::NONE_SELECTED) {
		// render
		render();

		// input
		input();

		// physics
		physics();

	}

	return playerCount;
}

void IntroPage::render() {
	clear();

	move(0, 0);
	printw("%d\n", currentCursor);
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
			case Cursor::ONE_PERSON:
				break;
			case Cursor::TWO_PEOPLE:
				break;
			case Cursor::EXIT:
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
