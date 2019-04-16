//
// Created by 박현근 on 2019-04-15.
//

#ifndef TETRIS_STAGECONTEXT_H
#define TETRIS_STAGECONTEXT_H

#include <map>

using namespace std;

class StageContext {
public:
	enum Status {
		CONTINUE,
		STOP
	};

	Status status = CONTINUE;
private:
	map<string, string> context;
};


#endif //TETRIS_STAGECONTEXT_H
