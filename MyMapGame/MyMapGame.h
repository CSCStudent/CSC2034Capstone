#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class MyMapGame
{
private:
	static const int NumberCities = 30;
	string Cityies[NumberCities];
	int Distance[NumberCities][NumberCities];
	int CurrentPoint;

public:
	MyMapGame();
	~MyMapGame();
	vector<int> getNextCities();
	string getNameCity(int i);
	vector<int> getParametrOfCity(int i);
	void setCurrentPoint(int i);
	
	
};

