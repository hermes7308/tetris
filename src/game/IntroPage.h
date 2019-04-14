//
// Created by 박현근 on 2019-04-10.
//

#ifndef TETRIS_INTROPAGE_H
#define TETRIS_INTROPAGE_H

#include <string>
#include "../model/IntroPageResult.h"

static const int UP = 65;
static const int DOWN = 66;

class IntroPage {
public:
	enum Cursor {
		START = 0,
		EXIT,

		COUNT
	};

	IntroPageResult Start();

private:
	const char *TITLE[6] = {
			"████████╗███████╗████████╗██████╗ ██╗███████╗", // 45
			"╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝",
			"   ██║   █████╗     ██║   ██████╔╝██║███████╗",
			"   ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║",
			"   ██║   ███████╗   ██║   ██║  ██║██║███████║",
			"   ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝"
	};


	const char *AUTHOR = "Created by HERMES";
	const int WIDTH = 80;
	const int HEIGHT = 24;
	const int TITLE_ROWS = 6;
	const int TITLE_COLS = 45;

	const char *CURSOR_CHARECTOR = "➡";
	const char *CURSOR_SPACE = " ";

	IntroPageResult result = IntroPageResult::NONE_SELECTED;

	int currentCursor = START;

	int startY;
	int startX;
	int exitY;

	int key;

	void up();

	void down();

	void renderStaticView();

	void render();

	void input();

	void physics();
};


#endif //TETRIS_INTROPAGE_H
