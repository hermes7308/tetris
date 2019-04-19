//
// Created by 박현근 on 2019-04-15.
//

#ifndef TETRIS_STAGE_H
#define TETRIS_STAGE_H

#include <thread>
#include <chrono>
#include "StageContext.h"

using namespace std;
using namespace chrono;

class Stage {
public:
	virtual ~Stage();

	const int WIDTH = 80;
	const int HEIGHT = 24;

	void Start(StageContext *context);

	void Stop();

protected:
	virtual void drawStatic(StageContext *context) = 0;

	virtual void draw(StageContext *context) = 0;

	virtual void input(StageContext *context) = 0;

	virtual void physics(StageContext *context) = 0;

	bool isRunning() const;

	void setRunning(bool running);

	const milliseconds &getCurrentTime() const;

	void setCurrentTime(const milliseconds &currentTime);

	unsigned int getFrame() const;

	void setFrame(unsigned int frame);

private:
	thread inputThread;

	bool running = true;

	milliseconds currentTime;

	unsigned int frame = 10;

	milliseconds getCurrentMilliseconds();
};


#endif //TETRIS_STAGE_H
