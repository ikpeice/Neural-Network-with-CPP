#include "stdafx.h"
#include "Neural_Net.hpp"

Neural_Net::Neural_Net(vector<int> topology, vector<vector<double>>in, vector<vector<double>> tar)
{
	this->topology = topology;
	this->numLayers = topology.size();
	
	// input layer
	Layer *L = new Layer(in.size() * in.at(0).size());
	layers.push_back(L);

	// hidden layer
	for (int i = 0;i < numLayers;i++) {
		L = new Layer(topology.at(i));
		layers.push_back(L);
	}

	// output layer
	L = new Layer(tar.size());
	layers.push_back(L);

	outputLayerIndex = layers.size() - 1;

	setInputValues(in);
	setTarget(tar);

	Matrix *M = nullptr;

	for (int i = 0;i < layers.size()-1;i++) {
		M = new Matrix(layers.at(i+1)->getNumNeurons(), layers.at(i)->getNumNeurons(), true);
		weightMatrixs.push_back(M);
		Matrix *c = new Matrix(layers.at(i + 1)->getNumNeurons(), 1, false);
		errors.push_back(c);
	}

}

void Neural_Net::setInputValues(vector<vector<double>> in)
{
	//assert(layers.at(0)->getNumNeurons() == inputs.size());
	//inputMatrix = new Matrix(inputs.size(), inputs.at(0).size(), false);
	int pos = 0;
	for (int r=0;r < in.size();r++) {
		for (int c = 0;c < in.at(0).size(); c++) {
			layers.at(0)->setNeuron(in.at(r).at(c), pos);
			pos++;
		}
		
	}
}

void Neural_Net::setTarget(vector<vector<double>> targets)
{
	Matrix *m = new Matrix(targets.size(),targets.at(0).size(), false);
	for (int r = 0;r < targets.size();r++) {
		for (int c = 0;c < targets.at(0).size();c++) {
			m->setValue(r, c, targets.at(r).at(c));
		}
	}
	target = m;
}

void Neural_Net::logError(Matrix *err)
{
	double tempError = 0.0;
	static double errorSum = 0.00;
	for (int i = 0; i < err->getNumRows(); i++) {
		tempError += err->getValue(i, 0);
	}
	historicalError.push_back(tempError);
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

		// forward propagation 
		for (unsigned i = 0;i < layers.size()-1 ;i++) {
			if (i == 0) {
				a = layers.at(i)->getInputMatrix();
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
				errors.at(i-1) = target->minus(Y);
				
				H = layers.at(i - 1)->getNeuronMatrix();
				//H = H->transpose();
	
				//H->printValues();
				//errors.at(i - 1)->multiply(sigmoid_derivative(Y))->printValues();
				delta_weight = errors.at(i - 1)->multiply(sigmoid_derivative(Y))->dot(H->transpose());
				//delta_weight->printValues();
				//weightMatrixs.at(i - 1)->printValues();
				weightMatrixs.at(i - 1) = weightMatrixs.at(i - 1)->plus(delta_weight);
				
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
			logError(errors.at(i - 1));

		}

		system("cls");
		cout <<"Training ... "<< (float(k) / float(num_Iteration)) * 100.00 << "%";

	}

	cout << "DONE!\n===============\n";
	Sleep(2000);
	//layers.at(outputLayerIndex)->getNeuronMatrix()->printValues();
}

void Neural_Net::predict(vector<vector<double>> data)
{
	Matrix *input = new Matrix(data.size()*data.at(0).size(), 1,false);
	// fill in the data
	int p = 0;
	for (int r = 0; r < data.size();r++) {
		for (int c = 0;c < data.at(0).size();c++) {
			input->setValue(p, 0, data.at(r).at(c));
			p++;
		}
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
