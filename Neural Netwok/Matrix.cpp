
#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix(int rows, int cols, bool isRandom)
{
	srand(time(NULL));
	this->numRows = rows;
	this->numCols = cols;

	// Initialze the matrix with some values
	
	
	for (int i = 0;i < rows;i++) {
		vector<double> colValues;
		for (int j = 0;j < cols;j++) {
			double v = 0.0;
			if (isRandom) {
				v =  getRandomNumber();
			}
			colValues.push_back(v);		// set col
		}
		Values.push_back(colValues); // set row
	}

}

Matrix * Matrix::operator*(Matrix &b)
{
	assert(this->numCols == b.numRows);
	Matrix *c = new Matrix(this->numRows, b.numCols, false);
	double v = 0.00;
	for (int i = 0;i < this->numRows;i++) {	// 3x2
		for (int j = 0;j < b.numCols;j++) {  //2x3
			for (int k = 0;k < b.numRows;k++) {
				v += this->getValue(i, k) * b.getValue(k, j);
			}
			c->setValue(i, j, v);
			v = 0.0;
		}
	}

	return c;
}

Matrix * Matrix::minus(Matrix *b)
{
	assert((this->numRows == b->numRows) && (this->numCols == b->numCols));
	Matrix *c = new Matrix(numRows, numCols, false);
	for (int i = 0;i < this->numRows;i++) {
		for (int j = 0;j < this->numCols;j++) {
			c->setValue(i, j, (this->getValue(i, j) - b->getValue(i, j)));
		}
	}
	return c;
}

Matrix * Matrix::plus(Matrix *b)
{
	assert((this->numRows == b->numRows) && (this->numCols == b->numCols));
	Matrix *c = new Matrix(numRows, numCols, false);
	for (int i = 0;i < this->numRows;i++) {
		for (int j = 0;j < this->numCols;j++) {
			c->setValue(i, j, (this->getValue(i, j) + b->getValue(i, j)));
		}
	}
	return c;
}

Matrix * Matrix::operator-(double scalar)
{
	//assert((this->numRows == b.numRows) && (this->numCols == b.numCols));
	Matrix *c = new Matrix(numRows, numCols, false);
	for (int i = 0;i < this->numRows;i++) {
		for (int j = 0;j < this->numCols;j++) {
			c->setValue(i, j, (this->getValue(i, j) - scalar));
		}
	}
	return c;
}

Matrix*  Matrix::transpose()
{
	Matrix *m = new Matrix(numCols, numRows, false);
	for (int i = 0;i < numRows;i++) {
		for (int j = 0;j < numCols;j++) {
			m->setValue(j, i, this->getValue(i, j));
		}
	}
	return m;
}

void Matrix::setValue(int r, int c, double v)
{
	Values.at(r).at(c) = v;
}

double Matrix::getValue(int r, int c)
{
	return Values.at(r).at(c);
}

double Matrix::getRandomNumber()
{
	return (rand() / double(RAND_MAX));
}

void Matrix::printValues()
{
	for (int i = 0;i < numRows;i++) {
		for (int j = 0;j < numCols;j++) {
			cout << Values.at(i).at(j) << "\t";
		}
		cout << endl;
	}
}

Matrix* Matrix::multiply(Matrix *b)
{
	assert(this->numCols == b->numRows);
	Matrix *c = new Matrix(this->numRows, b->numCols, false);
	double v = 0.00;
	for (int i = 0;i < this->numRows;i++) {	// 3x2
		for (int j = 0;j < b->numCols;j++) {  //2x3
			for (int k = 0;k < b->numRows;k++) {
				v += this->getValue(i, k) * b->getValue(k, j);
			}
			c->setValue(i, j, v);
			v = 0.0;
		}
	}

	return c;
}
