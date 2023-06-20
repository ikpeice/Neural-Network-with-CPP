// Neural Netwok.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


using namespace std;


int main()
{

	vector<int> topology;
	topology.push_back(2);
	topology.push_back(2);
	topology.push_back(3);

	vector<vector<double>> inputs;
	inputs = {
		{0,0,1},
		{1,0,1},
		{0,1,0},
		{0,1,1},
		{0,0,1},
		{ 1,0,1 },
		{ 0,1,0 },
		{ 0,1,1 }
	};

	vector<vector<double>>target;
	target = { 
		{ 0 },
		{ 1 },
		{ 1 },
		{ 0 },
		{ 0 },
		{ 1 },
		{ 1 },
		{ 0 }
	};

	Neural_Net Nnet(topology, inputs, target);

	Nnet.train(100, 0.1);

	//Nnet.printErrors();
	vector<vector<double>> test;
	test = {
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,1 },
		{ 0,0,0 },
		{ 0,0,0 }
	};
	vector<vector<double>> test2;
	test2 = {
		{ 0,0,1 },
		{ 1,0,1 },
		{ 0,1,0 },
		{ 0,1,1 },
		{ 0,0,1 },
		{ 1,0,1 },
		{ 0,1,0 },
		{ 0,1,1 }
	};
	Nnet.predict(test2);
	Nnet.predict(test);

	cout << "\n---------------------\nDONE!";

	getchar();
    return 0;
}

