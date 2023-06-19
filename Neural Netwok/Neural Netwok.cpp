// Neural Netwok.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


using namespace std;


int main()
{
	
	//Neuron n(1.5);
	//

	//cout << "Val = " << n.getVal() << "\n";
	//cout << "Activate = " << n.getActivated() << endl;
	//cout << "Derived = " << n.getDerivedVal() << endl;
	//Matrix M(1, 3, true);
	//Matrix b(1, 3, true);
	//M.transpose()->printValues();
	//cout << "---------------------" << endl;
	//Matrix *c = M.multiply(b.transpose());
	//c->printValues();
	//cout << "---------------------" << endl;
	//b.printValues();
	//cout << "---------------------" << endl;
	//Matrix *mM = M.multiply(&b);  // M x b

	//mM->printValues();
	//cout << "---------------------" << endl;
	//Matrix *mT = M.transpose();
	//mT->printValues();


	vector<int> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(3);

	vector<double> inputs;
	inputs.push_back(1.0);
	inputs.push_back(0.0);
	inputs.push_back(1.0);

	Neural_Net Nnet(topology);
	Nnet.setInputValues(inputs);
	Nnet.setTarget(inputs);
	Nnet.train(1);
	//Nnet.feedForward();
	//Nnet.setError();

	//Nnet.printToConsole();

	//cout << "Total error = " << Nnet.getTotalError() << endl;

	//Nnet.backPropagation();

	cout << "\n---------------------\nDONE!";

	getchar();
    return 0;
}

