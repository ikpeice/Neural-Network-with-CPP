#include "stdafx.h"
#include "Neuron.h"

Neuron::Neuron(double val)
{
	this->val = val;
	activate();
	//derive();

}

Neuron::~Neuron()
{
}
// fast sigmoid function
// f(x) = 1/(1 + exp(-x))
void Neuron::activate()
{
	this->activated_val = (1 / (1 + exp(-this->val)));
}
// fast derivative sigmoid function
//f(x)` = f(x) * (1 - f(x))
void Neuron::derive()
{
	derived_val = activated_val * (1 - activated_val);
}
