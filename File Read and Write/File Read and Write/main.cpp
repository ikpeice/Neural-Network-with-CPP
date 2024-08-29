#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"


using namespace std;

Vector<Vector<string>> rows;

string readUntil(ifstream file, const char t) {
	if (file.is_open()) {
		//file.read();
	}
	return "";
}

void write_head(string s) {
	int x[10] = { 5 };
	cout << "hello" << endl;
	ofstream myFile;
	myFile.open("data.csv");
	if (myFile.is_open()) {
		for (int i : x)myFile << "12,34,65,3,0.45,09" << endl;
		myFile.close();
	}
}

Vector<string> readSD() {
	ifstream dataFile;
	Vector<string> ds;
	char d[200];
	dataFile.open("data.csv");
	if (dataFile.is_open()) {
		while (!dataFile.eof()) {
			dataFile.read(d, 200);
			ds.append(string(d));
		}
		d[strlen(d)] = (char)EOF;
		ds.append(string(d));

		dataFile.close();
	}
	for (char i : ds.at(0)) {
		if (i == EOF)break;
		cout << i ;
	}
	return ds;
}





void main() {
	readSD();
	int v = getchar();
}