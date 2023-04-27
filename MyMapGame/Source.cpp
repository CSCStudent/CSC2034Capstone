#include "MyMapGame.h"
#include <iostream>

using namespace std;

int main() {
	//create an instance of a class
	MyMapGame a;

	//get indexes of three cities
	vector <int> dist = a.getNextCities();

	for (int i = 0; i < 3; i++) {
		cout << dist[i] << "   " << a.getNameCity(dist[i]) << endl;

		vector <int> Riv_Moun_Acc = a.getParametrOfCity(i);
		cout << Riv_Moun_Acc[0] << "  "<< Riv_Moun_Acc[1] << "  "<< Riv_Moun_Acc[2] <<endl;
	}



	//cout<<a.getNameCity(2)<<endl;

	//cout << a.getNameCity(5) << endl;
	

	//cout << "333"<<endl;


	return 0;
}