#include "DataBase.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>
//#include "stdafx.h"
#include "windows.h"

using namespace std;

DataBase::DataBase() {
	version = 0;

	string NameFile = "Data/country_capitals.txt";
	char delimiter = ',';

	string line;

	std::ifstream in(NameFile); 
	if (in.is_open())
	{
		while (getline(in, line))
		{
			
			//Venezuela, Caracas, 10.483333333333333, -66.866667, VE, South America

			vector<string> ParsStr;
			while (line.find(delimiter) != string::npos) {
				int tempNum = line.find(delimiter);
				string tempStr = line.substr(0, tempNum);
				line = line.substr(tempNum + 1, line.size() - tempNum);
				ParsStr.push_back(tempStr);
			}
			ParsStr.push_back(line);
			if (ParsStr.size() != 6)
				continue;
		
			if (ParsStr[1]._Equal("N/A") == 1 || ParsStr[1]._Equal("") == 1)
				continue;

			City tempCity;
			tempCity.Ñontinent = ParsStr[5];
			tempCity.Ñountry = ParsStr[0];
			tempCity.Capital = ParsStr[1];

			double X = 0.0;
			try {
				X = stod(ParsStr[2]);			
			}
			catch (const char* error_message) {
				cout << error_message << endl;
				continue;
			}

			double Y = 0.0;
			try {
				Y = stod(ParsStr[3]);
			}
			catch (string error_message) {
				cout << error_message << endl;
				continue;
			}

			tempCity.Latitude = X;
			tempCity.Longitude = Y;

			if (tempCity.Latitude != 0 && tempCity.Longitude != 0)
				Data.push_back(tempCity);
			
		}
	}
	in.close();     

	return;

}

DataBase::~DataBase() {
	Data.clear();
}

string DataBase::getDescriprionSity(int i) {
	if (i >= 0 && i < Data.size()) {
		City tempCity = Data[i];
		return "" + tempCity.Capital + " (" + tempCity.Ñountry + ")";
	}
	else
		return "check " + i;
	
}

int DataBase::gatNumberPointsInDataBase() {
	return Data.size();
}

vector<int> DataBase::getNextSitys(int Point, vector<int>SetPoints) {

	double CurrentX = Data[Point].Latitude;
	double CurrentY = Data[Point].Longitude;

	vector<int> rezult;
	rezult.push_back(-1);
	rezult.push_back(-1);
	rezult.push_back(-1);
	rezult.push_back(-1);


	int dist1 = 99999999;
	int dist2 = 99999999;
	int dist3 = 99999999;
	int dist4 = 99999999;

	for (int i = 0; i < Data.size(); i++) {
		if (i == Point)
			continue;
		if (count(SetPoints.begin(), SetPoints.end(), i))
			continue;
		
		double maxLongitude = max(Data[i].Longitude, CurrentY);
		double minLongitude = min(Data[i].Longitude, CurrentY);
		double distY;

		if (maxLongitude > 90 && minLongitude < -90)
			distY = ((180 - maxLongitude) + (180 + minLongitude))*100;
		else 
			distY = abs(Data[i].Longitude * 100 - CurrentY * 100);



		int dist = abs(Data[i].Latitude * 100 - CurrentX * 100) + distY;

		if (Data[i].Latitude > CurrentX && Data[i].Longitude > CurrentY)
			if (dist < dist1) {
				dist1 = dist;
				rezult[0] = i;
			}	
		if (Data[i].Latitude < CurrentX && Data[i].Longitude > CurrentY)
			if (dist < dist2) {
				dist2 = dist;
				rezult[1] = i;
			}	
		if (Data[i].Latitude > CurrentX && Data[i].Longitude < CurrentY)
			if (dist < dist3) {
				dist3 = dist;
				rezult[2] = i;
			}	
		if (Data[i].Latitude < CurrentX && Data[i].Longitude < CurrentY)
			if (dist < dist4) {
				dist4 = dist;
				rezult[3] = i;
			}
	}

	
	sort(rezult.begin(), rezult.end());

	vector<int> rezult_;
	for (int i = 0; i < 4; i++)
		if (rezult[i] != -1)
			rezult_.push_back(rezult[i]);

	return rezult_;

}

string DataBase::getLatLong(int Point) {
	if (Point > 0 && Point < Data.size())
		return to_string(Data[Point].Latitude) + ", " + to_string(Data[Point].Longitude);
	else
		return "";
}

string DataBase::getCapital(int Point) {
	if (Point > 0 && Point < Data.size())
		return Data[Point].Capital;
	else
		return "";
}

string DataBase::getHtmlMap(vector<int> Path, int FinishPoint, vector<int>NextPoints) {

	version++;
	string verStr = "";
	if (version > 99)
		verStr.append(to_string(version));
	else
		if (version > 9) {
			verStr.append("0");
			verStr.append(to_string(version));
		}
		else {
			verStr.append("00");
			verStr.append(to_string(version));
		}

	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile(L".\\Data\\flag*.png", &FindFileData);

	wstring fileWS = FindFileData.cFileName;
	string  fileSTR(fileWS.begin(), fileWS.end());

	// Initializing a string object
	string str = ".\\Data\\" + fileSTR;// +fileSTR;//FindFileData.cFileName;//".\\Data\\flag*";
	
	// Initializing an object of wstring
	wstring temp = wstring(str.begin(), str.end());// str.begin(), str.end());

	// Applying c_str() method on temp
	LPCWSTR src = temp.c_str();


	// Initializing a string object
	string str_ = ".\\Data\\flag"+ verStr +".png";

	// Initializing an object of wstring
	wstring temp_ = wstring(str_.begin(), str_.end());

	// Applying c_str() method on temp
	LPCWSTR dst = temp_.c_str();

	
	MoveFile(src, dst);
	
	string part1 = "<!DOCTYPE html> \n";
	part1.append("<html> \n");
	part1.append("<head> \n");
	part1.append("   <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/> \n");
	part1.append("   <meta http-equiv=\"X-UA-Compatible\" content=\"IE=9\"/>\n");
	part1.append("   <link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.6.0/dist/leaflet.css\" \n");
	part1.append("   integrity=\"sha512-xwE/Az9zrjBIphAcBb3F6JVqxf46+CDLwfLMHloNu6KEQCAWi6HcDUbeOfBIptF7tcCzusKFjFw2yuvEpDL9wQ==\"\n");
	part1.append("   crossorigin=\"\"/>\n");
	part1.append("   <script src=\"https://unpkg.com/leaflet@1.6.0/dist/leaflet.js\"\n");
	part1.append("   integrity=\"sha512-gZwIG9x3wUXg2hdXF6+rVkLF/0Vi9U8D2Ntg4Ga5I5BZpVkVxlJWbSQtXPSiUTtC0TjtGOmxa1AJPuV0CPthew==\"\n");
	part1.append("   crossorigin=\"\"></script>\n");
	part1.append("</head> \n");
	part1.append("<body> \n");
	part1.append("   <div id=\"map\" class=\"map\" style=\"position: absolute; top: 0px; right: 0px; bottom: 0px; left: 0px; \"></div>\n");
	part1.append("   <script type=\"text/javascript\">\n");
	//part1.append("      var odd = -1;\n");
	part1.append("      function sayHello() {\n");
	//part1.append("         var version = \""+verStr+"\";\n");
	part1.append("         var img = new Image();\n");
	part1.append("         img.src = './Data/flag"+ verStr +".png';\n");
	part1.append("         img.onerror = function(){location.reload()};\n");
	part1.append("      }\n");
	part1.append("      setInterval(sayHello, 1000);\n");
	part1.append("\n");
	part1.append("      var map = L.map('map').setView([0, 0],2);\n");
	part1.append("      L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png?{foo}', {foo: 'bar', attribution: 'Map data &copy; <a href=\"https://www.openstreetmap.org/\">OpenStreetMap</a> contributors, <a href=\"https://creativecommons.org/licenses/by-sa/2.0/\">CC-BY-SA</a>'}).addTo(map);\n");

	string part2 = "";
	string part3 = "";
	for (int i : Path) {
		part2.append("         var marker = L.marker([" + getLatLong(i) + "], {title:'" + getCapital(i) + "'}).addTo(map);\n");
		if (part3 > "")
			part3.append(",");
		part3.append("[" + getLatLong(i) + "]");
	}

	part2.append("         var LeafIcon = L.Icon.extend({options: {shadowUrl: 'Data/icons8.png',iconSize : [48, 48] ,shadowSize : [51, 37] ,iconAnchor : [16, 37] ,shadowAnchor : [16, 37] ,popupAnchor : [0, -30]}});\n");
	part2.append("         var LeafIcon = L.Icon.extend({options: {shadowUrl: 'Data/icons9.png',iconSize : [48, 48] ,shadowSize : [51, 37] ,iconAnchor : [16, 37] ,shadowAnchor : [16, 37] ,popupAnchor : [0, -30]}});\n");
	part2.append("         var coffeeIcon = new LeafIcon({ iconUrl: 'Data/icons8.png' });\n");
	part2.append("         var hintIcon = new LeafIcon({ iconUrl: 'Data/icons9.png' });\n");
	part2.append("         var marker = L.marker([" + getLatLong(FinishPoint) + "], {icon: coffeeIcon, title:'" + getCapital(FinishPoint) + "'}).addTo(map); \n");

	for (int i : NextPoints) {
		if (getCapital(i) != "")
			part2.append("         var marker = L.marker([" + getLatLong(i) + "], {icon: hintIcon, title:'" + getCapital(i) + "'}).addTo(map); \n");
	}
		
	part1.append(part2);
	part1.append("         var altlatlngs = [");
	part1.append(part3);
	part1.append("];\n");
	part1.append("         var altpolyline = L.polyline(altlatlngs, { color: 'blue', weight : 5, opacity : 0.7 }).addTo(map);\n");
	part1.append("         var altlatlngs2 = [[" + getLatLong(Path[0]) + "],[" + getLatLong(FinishPoint) + "]];\n");
	part1.append("         var altpolyline2 = L.polyline(altlatlngs2, { color: 'yellow', weight : 5, opacity : 0.7 }).addTo(map);\n");
	part1.append("         map.fitBounds(altpolyline.getBounds());\n");
	part1.append("         map.setView([0, 0], 2);\n");
	part1.append("   </script>\n");
	part1.append("</body>\n");
	part1.append("</html>");

	

	return part1;

}