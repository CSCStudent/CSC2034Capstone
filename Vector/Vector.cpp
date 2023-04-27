#define _USE_MATH_DEFINES	//M_PI

#include "Vector.h"
#include <math.h>		//cos
#include <numbers>		//M_PI
#include <algorithm>	//max
#include <ostream>
#include <string>

using namespace std;

Vector::Vector() {
	angle = 0;
	length = 0;
}

Vector::Vector(double an, double len) {
	angle = an;
	length = len;
}

Vector::~Vector() {
}

double Vector::getAngle() {
	return angle;
}

double Vector::getLength() {
	return length;
}

ostream& operator << (ostream& os, const Vector& v){

	//string str = v.length + " " + v.angle;

	//return os << v.length << " " << v.angle;

	
}

double operator * (const Vector& v1, const Vector& v2) {
	 
	return v1.length * v2.length * cos((v1.angle - v2.angle) * M_PI/180.0);

}

Vector operator + (const Vector& v1, const Vector& v2) {

	double length = pow(v1.length, 2) + pow(v2.length, 2) - 2 * v1.length * v2.length * cos((180 - (v1.angle - v2.angle)) * M_PI / 180.0);

	double angel = max(v1.angle, v2.angle) - abs(v1.angle - v2.angle)/2.0;
	
	return Vector(length, angel);

}