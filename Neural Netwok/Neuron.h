#pragma once
#ifndef NEURON_H
#define NEURON_H

#include "stdafx.h"
#include <iostream>


class Neuron
{
public:
	Neuron(double val);
	~Neuron();

	void activate();
	void derive();
	double getVal() { return val; }
	double getActivated() { activate(); return activated_val; }
	double getDerivedVal() { derive(); return derived_val; }
	void setValue(double value) { this->val = value; }
	//void setActivatedValue(double v) { activated_val = v; }
	void setDerivedValue(double v) { derived_val = v; }

private:
	double val;
	double activated_val = 0.00;
	double derived_val = 0.00;

};



#endif // !NEURON_H

