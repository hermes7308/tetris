//
// Created by 박현근 on 2019-04-10.
//

#ifndef TETRIS_INTROPAGE_H
#define TETRIS_INTROPAGE_H

#include <string>
#include "../core/Stage.h"

static const int UP = 65;
static const int DOWN = 66;

class IntroStage : public Stage {
public:
	enum Cursor {
		START = 0,
		EXIT,

		COUNT
	};
protected:
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

	const char *AUTHOR = "Created by HERMES";

	const char *CURSOR_CHARACTER = "➡"; // character
	int currentCursor = START;
	int startY{};
	int startX{};
	int exitY{};

	int key{};

	void up();

	void down();
};


#endif //TETRIS_INTROPAGE_H
