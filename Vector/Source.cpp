#include "Vector.h"
#include <iostream>

using namespace std;

int main() {
	Vector v1(20,35);
	Vector v2(12,0);

	Vector rezult = v1 + v2;

	cout << v1 << " + " << v2 << " = " << rezult << endl;

	return 0;
}