#include "DataBase.h"
#include "Play.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {

	const string fileOutput = "MyMap.html";
	
	DataBase DB;
	Play P(DB.gatNumberPointsInDataBase());
	
	cout << "Your task is to get from " << endl;
	cout << "    " << DB.getDescriprionSity(P.getStartPoint()) << endl;
	cout << "to" << endl;
	cout << "    " << DB.getDescriprionSity(P.getFinishPoint()) << endl;
	cout << "ATTENTION!!! \"0\" - hint for choosing a move" << endl << endl;

	vector<int> NextCitys;
	string htmlDoc = DB.getHtmlMap(P.getPath(), P.getFinishPoint(), NextCitys);
	ofstream out;
	out.open(fileOutput);
	if (out.is_open()) {
		out << htmlDoc;
	}
	out.close();

	system("MyMap.html");


	bool GameOver = false;
	while(!GameOver) {
		cout << "-------------------------" << endl;
		cout << "Select your next point:" << endl;
		NextCitys = DB.getNextSitys(P.getCurrentPoint(), P.getPath());
		for (int i = 0; i < NextCitys.size(); i++) {
			cout << (i + 1) << ". " << DB.getDescriprionSity(NextCitys[i]) << endl;
		}

		int SelectedCity = 0;
		while (SelectedCity < 1 || SelectedCity > NextCitys.size()) {
			cin >> SelectedCity;
			if (SelectedCity == 0) {
				string htmlDoc = DB.getHtmlMap(P.getPath(), P.getFinishPoint(), NextCitys);
				ofstream out;
				out.open(fileOutput);
				if (out.is_open()) {
					out << htmlDoc;
				}
				out.close();
			}
		}

		
		cout << "Great! Are you going to " << DB.getDescriprionSity(NextCitys[SelectedCity - 1]) << endl;
		GameOver = P.setCurrentPoint(NextCitys[SelectedCity - 1]);

		if (GameOver) {
			cout << endl;
			cout << "+++++++++++++++++++++++++++" << endl;
			cout << "Congratulations, you arrived on time!" << endl;
			cout << "It only took you " << P.getNumberMoves() << " flights to get from" << DB.getDescriprionSity(P.getStartPoint()) << "to" << DB.getDescriprionSity(P.getFinishPoint()) << endl << endl;
		}
		
		
		NextCitys.clear();
		string htmlDoc = DB.getHtmlMap(P.getPath(), P.getFinishPoint(), NextCitys);
		ofstream out;          
		out.open(fileOutput);
		if (out.is_open()){
			out << htmlDoc;
		}
		out.close();

	}

	return 0;

}