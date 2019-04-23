//
// Created by 박현근 on 2019-04-22.
//

#ifndef TETRIS_GAMEOVERSTAGE_H
#define TETRIS_GAMEOVERSTAGE_H


static const int ESC = 27;

#include <cstring>
#include <ncurses.h>
#include "../core/stage/Stage.h"

class GameOverStage : public Stage {
public:
	GameOverStage();

	~GameOverStage();

protected:
	void drawStatic(StageContext *context) override;

	void draw(StageContext *context) override;

	void input(StageContext *context) override;

	void physics(StageContext *context) override;

private:
	const char *TITTLE[6] = {
			" ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗",
			"██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
			"██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
			"██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
			"╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
			" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"
	};
	const int TITLE_ROWS = 6;
	const int TITLE_COLS = 74;
	const int GAME_OVER_WINDOW_HEIGHT = TITLE_ROWS + 2;
	const int GAME_OVER_WINDOW_WIDTH = TITLE_COLS + 2;
	const int GAME_OVER_WINDOW_Y = 3;
	const int GAME_OVER_WINDOW_X = (WIDTH - TITLE_COLS) / 2;
	WINDOW *gameOverTitleWindow;

	const char *GAME_OVER_EXPLANATION = "Press 'space' to continue, Press 'q' to exit.";
	const int GAME_OVER_EXPLANATION_HEIGHT = 1;
	const int GAME_OVER_EXPLANATION_WIDTH = static_cast<const int>(strlen(GAME_OVER_EXPLANATION));
	const int GAME_OVER_EXPLANATION_Y = GAME_OVER_WINDOW_Y + GAME_OVER_WINDOW_HEIGHT + 5;
	const int GAME_OVER_EXPLANATION_X = (WIDTH - GAME_OVER_EXPLANATION_WIDTH) / 2;
	WINDOW *gameOverExplanationWindow;

	int key{};
};


#endif //TETRIS_GAMEOVERSTAGE_H
