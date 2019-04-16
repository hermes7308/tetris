//
// Created by 박현근 on 2019-04-15.
//

#ifndef TETRIS_STAGE_H
#define TETRIS_STAGE_H


#include "StageContext.h"

class Stage {
public:
	const int WIDTH = 80;
	const int HEIGHT = 24;

	void Start(StageContext *context);

	void Stop();

protected:
	virtual void draw(StageContext *context) = 0;

	virtual void input(StageContext *context) = 0;

	virtual void physics(StageContext *context) = 0;

private:
	bool isRunning = true;

	void render(StageContext *context);
};


#endif //TETRIS_STAGE_H
