#include <iostream>
#include <stdio.h>
#include "vector.h"



using namespace std;

void print(){
	Vector<long> x;
	x.append(2);
	x.append(30);
	x.append(5);
	for (long i = 0; i < x.lenght(); i++) {
		cout << x.at(i) << endl;
	}
	cout << "Done A" << endl;
	x.replace(1, 100);
	for (long i = 0; i < x.lenght(); i++) {
		cout << x.at(i) << endl;
	}
}

void main() {
	int t = getchar();
	print();


	cout << "Done" << endl;

	int y=getchar();
}