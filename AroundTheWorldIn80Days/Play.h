#pragma once
#include <vector>
#include <string>
#include "DataBase.h"

using namespace std;

enum class Direction {EastToWest, WestToEast};

class Play
{
private:
	int StartPoint;
	int FinishPoint;
	int CurrentPoint;
	Direction DirectionOfTravel;
	vector<int> Path;

public:
	Play(int sizeDB);
	~Play();
	int getStartPoint();
	int getFinishPoint();
	int getCurrentPoint();
	vector<int> getPath();
	void setDirectionOfTravel(int d);
	bool setCurrentPoint(int i);
	int getNumberMoves();
	
};

