#include "stdafx.h"
#include "Neural_Net.hpp"

Neural_Net::Neural_Net(vector<int> topology, vector<vector<double>>in, vector<vector<double>> tar)
{
	this->topology = topology;
	this->numLayers = topology.size();

	if (in.size() != tar.size()) {
		cout << "Number of input must be equal to number of output!!\n";
		assert(false);
	}
	numInput = in.size();
	inputs = in;
	target = tar;
	
	// input layer
	Layer *L = new Layer(in.at(0).size());
	layers.push_back(L);

	// hidden layer
	for (int i = 0;i < numLayers;i++) {
		L = new Layer(topology.at(i));
		layers.push_back(L);
	}

	// output layer
	L = new Layer(tar.at(0).size());
	layers.push_back(L);

	outputLayerIndex = layers.size() - 1;

	//setInputValues(in);
	//setTarget(tar);

	Matrix *M = nullptr;

	for (int i = 0;i < layers.size()-1;i++) {
		M = new Matrix(layers.at(i+1)->getNumNeurons(), layers.at(i)->getNumNeurons(), true);
		weightMatrixs.push_back(M);
		Matrix *c = new Matrix(layers.at(i + 1)->getNumNeurons(), 1, false);
		errors.push_back(c);
	}

}

void Neural_Net::setInputValue(vector<vector<double>> in,int index)
{
	inputMatrix = new Matrix(in.at(index).size(),1, false);
	for (int r=0;r < in.at(index).size();r++) {
		inputMatrix->setValue(r, 0, in.at(index).at(r));
	}
}

void Neural_Net::setTarget(vector<vector<double>> tar,int index)
{
	targetMatrix = new Matrix(tar.at(index).size(),1, false);
	for (int r = 0;r < tar.at(index).size();r++) {
			targetMatrix->setValue(r, 0, tar.at(index).at(r));
	}
}

void Neural_Net::logError(Matrix *err)
{
	double tempError = 0.0;
	
	for (int i = 0; i < err->getNumRows(); i++) {
		tempError += err->getValue(i, 0);
	}
	historicalError.push_back(tempError);
	errorSum = tempError;
	tempError=0.0;

}

void Neural_Net::printErrors()
{
	cout << "\nPrinting Historical errors\n";
	for (unsigned int i = 0;i < historicalError.size();i++) {
		cout << historicalError.at(i) << endl;
	}
	
}

void Neural_Net::train(int num_Iteration, double Lrate)
{
	Matrix *error = nullptr;
	Matrix *delta_weight = nullptr;
	Matrix *Y = nullptr;
	Matrix *H = nullptr;
	
	//weightMatrixs.at(0)->transpose()->printValues();
	//cout << "=========\n";
	//weightMatrixs.at(1)->printValues();
	cout << "Training\n===============\n";
	//layers.at(0)->getNeuronMatrix()->printValues();
	Matrix *a = nullptr;
	for (int k = 0;k < num_Iteration;k++) {

		// for number of input
		for (int I = 0; I < numInput; I++) {

			setInputValue(inputs, I);
			setTarget(target, I);
			// forward propagation 
			for (unsigned i = 0;i < layers.size() - 1;i++) {
				if (i == 0) {
					a = inputMatrix;//layers.at(i)->getInputMatrix();
				}
				else {
					a = layers.at(i)->getNeuronMatrix();
				}
				Matrix *w = getWeigthMatrix(i);
				// c = Sum of = (W1*X1 + W2*X2 . . . Wn*Xn) +bi where i is number
				//cout << "i = " << i;

				Matrix *c = w->dot(a);
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
					//cout << "layer = " << i << endl;
					Y = layers.at(i)->getNeuronMatrix();
					// compute the error

					//target->printValues();
					//Y->printValues();
					errors.at(i - 1) = targetMatrix->minus(Y);
					logError(errors.at(i - 1));

					H = layers.at(i - 1)->getNeuronMatrix();
					//H = H->transpose();

					//H->printValues();
					//errors.at(i - 1)->multiply(sigmoid_derivative(Y))->printValues();
					delta_weight = errors.at(i - 1)->multiply(sigmoid_derivative(Y))->dot(H->transpose());
					//delta_weight->printValues();
					//weightMatrixs.at(i - 1)->printValues();
					weightMatrixs.at(i - 1) = weightMatrixs.at(i - 1)->minus(delta_weight);

				}
				else {

					Y = layers.at(i)->getNeuronMatrix();
					//cout << "ok Y\n";
					//Y->printValues();
					//errors.at(i)->printValues();
					//cout << "====\n";
					//weightMatrixs.at(i)->printValues();
					//cout << "ok1\n";
					errors.at(i - 1) = weightMatrixs.at(i)->transpose()->dot(errors.at(i));
					//cout << "ok2\n";
					//errors.at(i - 1)->printValues();
					H = layers.at(i - 1)->getNeuronMatrix();
					//H->printValues();
					//cout << "ok1\n";
					delta_weight = errors.at(i - 1)->multiply(sigmoid_derivative(Y))->dot(H->transpose());
					weightMatrixs.at(i - 1) = weightMatrixs.at(i - 1)->plus(delta_weight);
				}


			}
		}



		system("cls");
		cout <<"Training ... "<< (float(k) / float(num_Iteration)) * 100.00 << "%";

	}

	cout << "DONE!\n===============\n";
	Sleep(2000);
	//layers.at(outputLayerIndex)->getNeuronMatrix()->printValues();
}

void Neural_Net::predict(vector<double> data)
{
	Matrix *input = new Matrix(data.size(), 1,false);
	// fill in the data

	for (int r = 0; r < data.size();r++) {
			input->setValue(r, 0, data.at(r));
	}
	input->printValues();

	for (unsigned i = 0;i < layers.size() - 1;i++) {
		if (i > 0) {
			input = getNeuronMatrix(i);
		}

		Matrix *w = getWeigthMatrix(i);
		// c = Sum of = (W1*X1 + W2*X2 . . . Wn*Xn) +bi where i is number
		//cout << "i = " << i;

		Matrix *c = w->dot(input);
		sigmoid_activate(c);
		//c->printValues();

		// update the next layer neurons
		for (unsigned j = 0;j < c->getNumRows();j++) {
			setNeuronValue(i + 1, j, c->getValue(j, 0));
		}
		//cout << "===============\n";
	}
	cout << ">>>\n===============\n";

	getNeuronMatrix(outputLayerIndex)->printValues();
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
			v = 2*v * (1 - v);
			c->setValue(i, j, v);
		}
	}
	return c;
}
