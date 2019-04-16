cmake_minimum_required(VERSION 3.13)
project(tetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lncurses")

add_executable(tetris src/main.cpp src/timer/GameTimer.cpp src/timer/GameTimer.h src/timer/PlayTimer.cpp src/timer/PlayTimer.h src/game/Tetris.cpp src/game/Tetris.h src/game/IntroStage.cpp src/game/IntroStage.h src/core/Stage.cpp src/core/Stage.h src/core/StageContext.cpp src/core/StageContext.h src/block/Block.cpp src/block/Block.h src/block/BlockI.cpp src/block/BlockI.h src/block/BlockJ.cpp src/block/BlockJ.h src/block/BlockL.cpp src/block/BlockL.h src/block/BlockO.cpp src/block/BlockO.h)