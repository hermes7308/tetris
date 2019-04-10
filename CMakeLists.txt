cmake_minimum_required(VERSION 3.13)
project(tetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lncurses")

add_executable(tetris src/main.cpp src/timer/GameTimer.cpp src/timer/GameTimer.h src/timer/PlayTimer.cpp src/timer/PlayTimer.h src/game/Tetris.cpp src/game/Tetris.h src/game/IntroPage.cpp src/game/IntroPage.h src/model/PlayerCount.cpp src/model/PlayerCount.h)