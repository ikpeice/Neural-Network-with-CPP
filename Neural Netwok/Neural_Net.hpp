#pragma once
#ifndef NEURAL_NET
#define NEURAL_NET

#include "stdafx.h"
#include "Neural_Net.hpp"

class Neural_Net
{
public:
	Neural_Net(vector<int> topology);
	void setInputValues(vector<double> inputs);
	void setTarget(vector<double> targets);
	//void setError();
	void printToConsole();
	void train(int num_Iteration);
	void feedForward();
	void backPropagation();
	void setNeuronValue(int layerIndex, int neuronIndex, double value);



	Matrix *getNeuronMatrix(int layerIndex);
	Matrix *getActivatedMatrix(int layerIndex);
	Matrix *getDerivedMatrix(int layerIndex);
	Matrix *getWeigthMatrix(int layerIndex);

	vector<double> getErrors() { return errors; }
	
	double getTotalError() { return errorSum; }



private:
	int topologySize;
	int outputLayerIndex;
	Matrix *target = nullptr;
	vector<int> topology;
	vector<Layer*> layers;
	vector<Matrix*> weightMatrixs;
	vector<Matrix *> gradientMatrixs;
	void sigmoid_activate(Matrix *m);
	Matrix *sigmoid_derivative(Matrix *m);
	
	vector<double> inputs;

	//vector<double> target;
	double errorSum;
	vector<double> errors;
	vector<double> historicalError;
};


#endif // !NEURAL_NET
