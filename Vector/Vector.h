#pragma once
class Vector
{
private:
	double angle;
	double length;
	
public:
	Vector();
	Vector(double angle, double length);
	~Vector();

	//getters
	double getAngle();
	double getLength();

	//Friend fuctions
	friend double operator * (const Vector&, const Vector&); //get the dot product of vectors
	friend Vector operator + (const Vector&, const Vector&); //get the sum of two vectors
	friend Vector operator - (const Vector&, const Vector&); //get the difference of two vectors
	friend ostream& operator << (ostream& os, const Vector&);
};

