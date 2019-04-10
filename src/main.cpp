
#include <ncurses.h>
#include "game/IntroPage.h"

void setup() {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
}

int main() {

    setup();

    // intro
    // player one, player two
    IntroPage *introPage = new IntroPage();
	introPage->Start();

    // physics

    // render

}