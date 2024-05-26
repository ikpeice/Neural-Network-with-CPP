#pragma once
#ifndef LAYER_HPP
#define LAYER_HPP

#include "stdafx.h"
#include "Neuron.h"

class Layer {
public:
	Layer(int numNeurons);
	int getNumNeurons() { return this->numNeurons; }
	void setInputNeuron(double value, int pos);
	void setNeuron(double value, int pos);
	Matrix *getInputMatrix();
	Matrix *getActivatedMatrix();
	Matrix *getDerivedMatrix(); 
	Matrix *getNeuronMatrix();
private:
	int numNeurons;
	vector<Neuron*> neurons;
};
#endif // !LAYER_HPP
