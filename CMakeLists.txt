cmake_minimum_required(VERSION 3.13)
project(tetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lncurses")

add_executable(tetris
        src/main.cpp
        src/core/block/Block.cpp
        src/core/block/Block.h
        src/core/block/BlockI.cpp
        src/core/block/BlockI.h
        src/core/block/BlockJ.cpp
        src/core/block/BlockJ.h
        src/core/block/BlockL.cpp
        src/core/block/BlockL.h
        src/core/block/BlockO.cpp
        src/core/block/BlockO.h
        src/core/block/BlockS.cpp
        src/core/block/BlockS.h
        src/core/block/BlockT.cpp
        src/core/block/BlockT.h
        src/core/block/BlockZ.cpp
        src/core/block/BlockZ.h
        src/core/stage/Stage.cpp
        src/core/stage/Stage.h
        src/core/stage/StageContext.cpp
        src/core/stage/StageContext.h
        src/stage/IntroStage.cpp
        src/stage/IntroStage.h
        src/stage/GameStage.cpp
        src/stage/GameStage.h
        src/stage/GameOverStage.cpp
        src/stage/GameOverStage.h
        src/stage/Tetris.cpp
        src/stage/Tetris.h)