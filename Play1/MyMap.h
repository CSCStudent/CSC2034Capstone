#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Map
{
private:
	
	string Cityies[30];

public:
	MyMap();
	~MyMap();
	vector<int> getNextCities();
	string getNameCity(int i);
	vector<int> getParametrOfCity(int i);


	MyMap(int s) {

		cout << s<<endl;

	}
};

