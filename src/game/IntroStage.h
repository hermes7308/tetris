//
// Created by 박현근 on 2019-04-10.
//

#ifndef TETRIS_INTROPAGE_H
#define TETRIS_INTROPAGE_H

#include <string>
#include "../core/Stage.h"


class IntroStage : public Stage {
public:
	enum Cursor {
		START = 0,
		EXIT,

		COUNT
	};
protected:
public:
	IntroStage();

	~IntroStage();

protected:
	void drawStatic(StageContext *context) override;

	void draw(StageContext *context) override;

	void input(StageContext *context) override;

	void physics(StageContext *context) override;

private:
	const char *TITLE[6] = {
			"████████╗███████╗████████╗██████╗ ██╗███████╗", // 45
			"╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝",
			"   ██║   █████╗     ██║   ██████╔╝██║███████╗",
			"   ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║",
			"   ██║   ███████╗   ██║   ██║  ██║██║███████║",
			"   ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝"
	};
	const int TITLE_ROWS = 6;
	const int TITLE_COLS = 45;
	const int TITLE_WINDOW_HEIGHT = TITLE_ROWS + 2;
	const int TITLE_WINDOW_WIDTH = TITLE_COLS + 2;
	const int TITLE_Y = 3;
	const int TITLE_X = (WIDTH - TITLE_COLS) / 2;
	WINDOW *titleWindow;

	const char *AUTHOR = "Created by HERMES";
	const int AUTHOR_WINDOW_HEIGHT = 1;
	const int AUTHOR_WINDOW_WIDTH = 20;
	const int AUTHOR_Y = TITLE_Y + TITLE_WINDOW_HEIGHT;
	const int AUTHOR_X = TITLE_X + (TITLE_COLS - AUTHOR_WINDOW_WIDTH);
	WINDOW *authorWindow;

	const char *SELECT_OPTIONS[Cursor::COUNT] = {"Start", "Exit"};
	const int SELECT_OPTION_HEIGHT = Cursor::COUNT;
	const int SELECT_OPTION_WIDTH = 5;
	const int SELECT_OPTION_Y = AUTHOR_Y + 5;
	const int SELECT_OPTION_X = TITLE_X + 3;
	WINDOW *selectOptionWindow;

	const char *SELECT_OPTION_CURSOR_CHARACTER = "➡"; // character
	const int SELECT_OPTION_CURSOR_HEIGHT = Cursor::COUNT;
	const int SELECT_OPTION_CURSOR_WIDTH = 1;
	const int SELECT_OPTION_CURSOR_Y = AUTHOR_Y + 5;
	const int SELECT_OPTION_CURSOR_X = TITLE_X;
	WINDOW *selectOptionCursorWindow;

	int currentCursor = START;

	int key{};

	void up();

	void down();

	void drawTitle();

	void drawAuthor();

	void drawSelectOption();

	void drawSelectOptionCursorWindow();
};


#endif //TETRIS_INTROPAGE_H
