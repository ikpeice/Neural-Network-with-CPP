#include "stdafx.h"
#include "Neural_Net.hpp"

Neural_Net::Neural_Net(vector<int> topology_)
{
	this->topology = topology_;
	this->topologySize = topology.size();
	for (int i = 0;i < topologySize;i++) {
		Layer *L = new Layer(topology.at(i));
		layers.push_back(L);
	}

	outputLayerIndex = layers.size() - 1;

	for (int i = 0;i < topologySize - 1;i++) {
		Matrix *M = new Matrix(topology.at(i+1), topology.at(i),true);
		weightMatrixs.push_back(M);
		Matrix *c = new Matrix(topology.at(i + 1),1, false);
		errors.push_back(c);

	}
}

void Neural_Net::setInputValues(vector<double> inputs)
{
	assert(layers.at(0)->getNumNeurons() == inputs.size());

	for (int i=0;i < inputs.size();i++) {
		layers.at(0)->setNeuron(inputs.at(i), i);

	}
}

void Neural_Net::setTarget(vector<double> targets)
{
	Matrix *m = new Matrix(1, targets.size(), false);
	for (int i = 0;i < targets.size();i++) {
		m->setValue(0, i, targets.at(i));
	}
	target = m;
}

//void Neural_Net::setError()
//{
//	assert(target.size() != 0);
//	assert(target.size() == layers.at(layers.size()-1)->getNumNeurons());
//	for (unsigned i = 0;i < target.size();i++) {
//		errors.push_back(0.00);
//	}
//	errorSum = 0.0;
//	double tempError = 0.0;
//	for (int i = 0; i < layers.at(layers.size() - 1)->getNumNeurons(); i++) {
//		tempError = (layers.at(layers.size() - 1)->getInputMatrix()->getValue(0, i) ) - target.at(i);
//		errorSum += tempError;
//		errors.at(i) = tempError;
//	}
//	historicalError.push_back(errorSum);
//
//}

void Neural_Net::printToConsole()
{
	Matrix *m = nullptr;
	for (unsigned int i = 0;i < layers.size();i++) {

		cout << "Layer: " << i << endl;
		m = layers.at(i)->getInputMatrix();
		m->printValues();
		cout << "========================" << endl;

		if (i < (layers.size() - 1)) {
			cout << "=====================" << endl;
			cout << endl << "WeightMatrix: " << i << endl;
			m = getWeigthMatrix(i);
			m->printValues();
			cout << "========================" << endl;
		}
	}
}

void Neural_Net::train(int num_Iteration)
{
	Matrix *error = nullptr;
	Matrix *delta_weight = nullptr;
	Matrix *Y = nullptr;
	Matrix *H = nullptr;
	weightMatrixs.at(0)->printValues();
	//cout << "=========\n";
	//weightMatrixs.at(1)->printValues();
	cout << "Start\n===============\n";
	//layers.at(outputLayerIndex)->getNeuronMatrix()->printValues();
	Matrix *a = nullptr;
	for (int k = 0;k < num_Iteration;k++) {

		// forward propagation 
		for (unsigned i = 0;i < layers.size() - 1;i++) {
			if (i == 0) {
				a = layers.at(i)->getInputMatrix();
			}
			else {
				a = layers.at(i)->getNeuronMatrix();
			}
			Matrix *w = getWeigthMatrix(i);
			// c = Sum of = (W1*X1 + W2*X2 . . . Wn*Xn) +bi where i is number
			//cout << "i = " << i;
			Matrix *c = w->dot(a->transpose()); 
			sigmoid_activate(c);
			//c->printValues();

			// update the next layer neurons
			for (unsigned j = 0;j < c->getNumRows();j++) {
				setNeuronValue(i + 1, j, c->getValue(j, 0));
			}
			//cout << "===============\n";
		}

		//layers.at(outputLayerIndex)->getNeuronMatrix()->printValues();
		//output = layers.at(outputLayerIndex)->getNeuronMatrix();


		// back propagation 
		//target->printValues();
		for (int i = outputLayerIndex; i >0; i--) {
			if (i == outputLayerIndex) {
				// extract the output layer values since it is already activated
				Y = layers.at(i)->getNeuronMatrix();
				// compute the error
				errors.at(i-1) = target->minus(Y);
				
				H = layers.at(i - 1)->getNeuronMatrix();
				H = H->transpose();
	
			
				//errors.at(i - 1)->multiply(sigmoid_derivative(Y))->printValues();
				delta_weight = H->dot(errors.at(i - 1)->multiply(sigmoid_derivative(Y)));

				weightMatrixs.at(i - 1) = weightMatrixs.at(i - 1)->plus(delta_weight->transpose());
				
			}
			else {
				
				Y = layers.at(i)->getNeuronMatrix();
				//cout << "ok1\n";
				//Y->printValues();
				//errors.at(i)->printValues();
				//cout << "====\n";
				//weightMatrixs.at(i)->transpose()->printValues();
				errors.at(i - 1) = weightMatrixs.at(i)->transpose()->dot(errors.at(i)->transpose());
				//cout << "ok2\n";
				//errors.at(i - 1)->printValues();
				H = layers.at(i - 1)->getNeuronMatrix();
				//H->printValues();

				delta_weight = errors.at(i - 1)->multiply(sigmoid_derivative(Y->transpose()))->dot(H);
				weightMatrixs.at(i - 1) = weightMatrixs.at(i - 1)->plus(delta_weight);
			}

		}

	}

	cout << "After\n===============\n";
	layers.at(outputLayerIndex)->getNeuronMatrix()->printValues();
}

void Neural_Net::feedForward()
{
	for (unsigned i = 0;i < layers.size()-1;i++) {
		Matrix *a = nullptr;
		if (i == 0) {
			a = layers.at(i)->getInputMatrix();
		}
		else {
			a = layers.at(i)->getNeuronMatrix();
		}
		Matrix *w = getWeigthMatrix(i);
		Matrix *c = a->multiply(w);
		//cout << "before ===============\n";
		//c->printValues();
		//cout << "after ===============\n";
		sigmoid_activate(c);
		//c->printValues();

		// set the next layer neurons
		for (unsigned j = 0;j < c->getNumCol();j++) {
			//layers.at(i+1)->setNeuron(c->getValue(0, j), j);
			setNeuronValue(i + 1, j, c->getValue(0, j));
			//cout << c->getValue(0, j)<<endl;
		}
		cout << "\n\n===============\n";
	}
}

void Neural_Net::backPropagation()
{
	//cout << "\nbackPropagation " << outputLayerIndex << endl;

	//Matrix *derivedValue_YtoZ = layers.at(outputLayerIndex)->getDerivedMatrix();
	////derivedValue_YtoZ->printValues();
	//Matrix *gradient_YtoZ = new Matrix(1, layers.at(outputLayerIndex)->getNumNeurons(), false);
	//double g = 0.00;
	//for (int i = 0; i < errors.size();i++) {
	//	g = derivedValue_YtoZ->getValue(0, i) * errors.at(i);
	//	gradient_YtoZ->setValue(0, i, g);
	//}

	////Layer *lastHiddenLayer = layers.at(outputLayerIndex);
	//Matrix *deltaWeight = gradient_YtoZ->transpose()->multiply(getActivatedMatrix(outputLayerIndex-1));
	//cout << "========================" << endl;
	//deltaWeight->transpose()->printValues();
	//deltaWeight = deltaWeight->transpose();
	//weightMatrixs.at(outputLayerIndex - 1) = weightMatrixs.at(outputLayerIndex - 1)->minus(deltaWeight);
	//cout << "========================" << endl;
	//weightMatrixs.at(outputLayerIndex - 1)->printValues();

	// get derived values for all hidden layers
	Matrix *error = nullptr;
	for (int i = outputLayerIndex; i > 0; i--) {
		error = target->minus(layers.at(i)->getNeuronMatrix());

	}

}

void Neural_Net::setNeuronValue(int layerIndex, int neuronIndex, double value)
{
	layers.at(layerIndex)->setNeuron(value, neuronIndex);
}

Matrix * Neural_Net::getNeuronMatrix(int layerIndex)
{
	Matrix *m = layers.at(layerIndex)->getInputMatrix();
	return m;
}

Matrix * Neural_Net::getActivatedMatrix(int layerIndex)
{
	Matrix *m = layers.at(layerIndex)->getActivatedMatrix();
	return m;
}

Matrix * Neural_Net::getDerivedMatrix(int layerIndex)
{
	Matrix *m = layers.at(layerIndex)->getDerivedMatrix();
	return m;
}

Matrix * Neural_Net::getWeigthMatrix(int layerIndex)
{
	//Matrix *m = weightMatrix.at(layerIndex);
	return weightMatrixs.at(layerIndex);
}



void Neural_Net::sigmoid_activate(Matrix *m)
{
	for (int i = 0;i < m->getNumRows();i++) {
		for (int j = 0;j < m->getNumCol();j++) {
			double v = m->getValue(i, j);
			v = 1 / (1 + exp(-v));
			m->setValue(i, j, v);
		}
	}
}

Matrix* Neural_Net::sigmoid_derivative(Matrix * m)
{
	Matrix *c = new Matrix(m->getNumRows(), m->getNumCol(), false);
	for (int i = 0;i < m->getNumRows();i++) {
		for (int j = 0;j < m->getNumCol();j++) {
			double v = m->getValue(i, j);
			v = v * (1 - v);
			c->setValue(i, j, v);
		}
	}
	return c;
}
