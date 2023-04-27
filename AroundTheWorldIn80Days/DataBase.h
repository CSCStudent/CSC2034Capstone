#include <vector>
#include <string>

using namespace std;

#pragma once

class City {
public:
	string Ñontinent;
	string Ñountry;
	string Capital;
	double Latitude;
	double Longitude;
};

class DataBase
{
private:
	vector<City> Data;
	int version;
public:
	DataBase();
	~DataBase();
	vector<int> getNextSitys(int Point, vector<int>SetPoints);
	string getDescriprionSity(int Point);
	int gatNumberPointsInDataBase();
	string getLatLong(int Point);
	string getCapital(int Point);
	string getHtmlMap(vector<int> Path, int FinishPoint, vector<int>NextPoints);
};

