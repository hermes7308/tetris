//
// Created by 박현근 on 2019-04-15.
//

#include "Stage.h"

Stage::Stage() {

}

Stage::~Stage() {
	Stop();
}

void Stage::Start(StageContext *context) {
	drawStatic(context);

	running = true;

	inputThread = thread([=]() {
		while (running) {
			input(context);
		}
	});

	while (running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frame));

		// set current time
		currentTime = getCurrentMilliseconds();

		// draw
		draw(context);

		// physics
		physics(context);
	}

	inputThread.join();
	Stop();
}

void Stage::Stop() {
	running = false;
}

milliseconds Stage::getCurrentMilliseconds() {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	return ms;
}

const milliseconds &Stage::getCurrentTime() const {
	return currentTime;
}

void Stage::setCurrentTime(const milliseconds &currentTime) {
	Stage::currentTime = currentTime;
}

unsigned int Stage::getFrame() const {
	return frame;
}

void Stage::setFrame(unsigned int frame) {
	Stage::frame = frame;
}

bool Stage::isRunning() const {
	return running;
}

void Stage::setRunning(bool running) {
	Stage::running = running;
}
