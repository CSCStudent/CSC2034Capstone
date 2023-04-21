#include "Play.h"
#include "DataBase.h"
#include <string>
#include <time.h>

Play::Play(int sizeDB) {
	srand(time(0));

	StartPoint = rand() % sizeDB;
	FinishPoint = rand() % sizeDB;

	while(StartPoint == FinishPoint)
		FinishPoint = rand() % sizeDB;

	CurrentPoint = StartPoint;
	Path.push_back(StartPoint);

}

Play::~Play() {
	Path.clear();
}

int Play::getStartPoint() {
	return StartPoint;
}

int Play::getFinishPoint() {
	return FinishPoint;
}

int Play::getCurrentPoint() {
	return CurrentPoint;
}

vector<int> Play::getPath() {
	return Path;
}

bool Play::setCurrentPoint(int i) {
	CurrentPoint = i;
	if (i == FinishPoint)
		return true;
	else {
		Path.push_back(i);
		return false;
	}
}

int Play::getNumberMoves() {
	return Path.size();
}

