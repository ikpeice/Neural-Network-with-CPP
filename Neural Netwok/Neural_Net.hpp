#pragma once
#ifndef NEURAL_NET
#define NEURAL_NET

#include "stdafx.h"
#include "Neural_Net.hpp"

class Neural_Net
{
public:
	Neural_Net(vector<int> topology, vector<vector<double>> inputs, vector<vector<double>> targets);
	void setInputValues(vector<vector<double>> inputs);
	void setTarget(vector<vector<double>> targets);
	void logError(Matrix *err);
	void printErrors();
	void train(int num_Iteration,double Lrate);
	void predict(vector<vector<double>> data);
	void backPropagation();
	void setNeuronValue(int layerIndex, int neuronIndex, double value);



	Matrix *getNeuronMatrix(int layerIndex);
	Matrix *getActivatedMatrix(int layerIndex);
	Matrix *getDerivedMatrix(int layerIndex);
	Matrix *getWeigthMatrix(int layerIndex);

	//vector<double> getErrors() { return errors; }
	
	//double getTotalError() { return errorSum; }



private:
	int numLayers;
	int outputLayerIndex;
	Matrix *inputMatrix = nullptr;
	Matrix *target = nullptr;
	vector<int> topology;
	vector<Layer*> layers;
	vector<Matrix*> weightMatrixs;
	vector<Matrix *> gradientMatrixs;
	vector<Matrix *> errors;
	void sigmoid_activate(Matrix *m);
	Matrix *sigmoid_derivative(Matrix *m);
	
	//vector<double> inputs;

	//vector<double> target;
	double errorSum;
	//vector<double> errors;
	vector<double> historicalError;
};


#endif // !NEURAL_NET
