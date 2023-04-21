#include "MyMapGame.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out)
{
	// строим поток из строки
	std::stringstream ss(str);

	std::string s;
	while (std::getline(ss, s, delim)) {
		out.push_back(s);
	}
}

MyMapGame::MyMapGame() {

	
	ifstream work_file("data.csv");
	//ifstream work_file("data.txt");
	string line;
	char delimiter = ';';
	CurrentPoint = 0;

	getline(work_file, line);

	int num = 0;
	while (getline(work_file, line))
	{
		//stringstream str(line);
		//cout << line << endl;
		//Cityies[num] = line;

		vector<string> out;
		tokenize(line, ';', out);
		
		int numY = 0;
		for (auto& s : out) {
			if (numY==0)
				Cityies[num] = s;
			else
				Distance[num][numY] = stoi(s);
			numY++;
			if (numY >= MyMapGame::NumberCities)
				break;
		}

		num++;
		if (num >= MyMapGame::NumberCities)
			break;
	}
	work_file.close();

}

MyMapGame::~MyMapGame() {
	Cityies->clear();
}

vector<int> MyMapGame::getNextCities() {

	vector <int> rezult;

	srand(time(0));

	while (rezult.size() < 3) {
		int index = rand() % MyMapGame::NumberCities;
		bool flag = true;
		for (int i = 0; i < rezult.size(); i++) {
			if (rezult[i] == index)
				flag = false;
		}

		if (flag)
			rezult.push_back(index);
	}

	return rezult;

}

string MyMapGame::getNameCity(int i) {

	return Cityies[i];

}

void MyMapGame::setCurrentPoint(int i) {
	CurrentPoint = i;
}

vector<int> MyMapGame::getParametrOfCity(int i) {

	vector <int> rezult;

	int distance = Distance[CurrentPoint][i];

	srand(time(0)+i);

	rezult.push_back(1 + rand() % 10);
	rezult.push_back(11 + rand() % 10);
	rezult.push_back(21 + rand() % 10);
	
	return rezult;

}



