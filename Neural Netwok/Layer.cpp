#include "Layer.hpp"
#include "stdafx.h"

Layer::Layer(int numNeurons_)
{
	this->numNeurons = numNeurons_;
	for (int i = 0; i < numNeurons;i++) {
		Neuron *n = new Neuron(0.0);
		neurons.push_back(n);
	}
}
void Layer::setInputNeuron(double value, int pos)
{
	neurons.at(pos)->setValue(value);
	
}

void Layer::setNeuron(double value,int pos)
{
	neurons.at(pos)->setValue(value);
	//neurons.at(pos)->activate();
}

Matrix * Layer::getInputMatrix()
{
	Matrix *M = new Matrix(1, numNeurons, false);
	for (int i = 0;i < numNeurons;i++) {
		M->setValue(0, i, neurons.at(i)->getVal());
	}
	return M;
}

Matrix * Layer::getActivatedMatrix()
{
	Matrix *M = new Matrix(1, numNeurons, false);
	for (int i = 0;i < numNeurons;i++) {
		neurons.at(i)->activate();
		M->setValue(0, i, neurons.at(i)->getActivated());
	}
	return M;
}

Matrix * Layer::getDerivedMatrix()
{
	Matrix *M = new Matrix(1, numNeurons, false);
	for (int i = 0;i < numNeurons;i++) {
		neurons.at(i)->derive();
		M->setValue(0, i, neurons.at(i)->getDerivedVal());
	}
	return M;
}
Matrix * Layer::getNeuronMatrix()
{
	Matrix *M = new Matrix(1, numNeurons, false);
	for (int i = 0;i < numNeurons;i++) {
		M->setValue(0, i, neurons.at(i)->getVal());
	}
	return M;
}