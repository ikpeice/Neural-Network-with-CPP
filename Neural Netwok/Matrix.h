#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

class Matrix {
public:
	Matrix(){}
	Matrix(int rows, int cols, bool isRandom,double v=0.0);
	Matrix* operator*(Matrix &b);
	Matrix* minus(Matrix *b);
	Matrix *plus(Matrix *b);
	Matrix* operator-(double scalar);
	Matrix* transpose();
	void setValue(int r, int c, double v);
	void setMatrix(int r_size, int c_size, double v[][3]);
	double getValue(int r, int c);
	double getRandomNumber();
	void printValues();
	int getNumCol() { return numCols; }
	int getNumRows() { return numRows; }
	Matrix *dot(Matrix *b);
	Matrix *multiply(Matrix *b);

private:
	vector< vector<double>> Values;
	int numRows,numCols;
};
#endif // !MATRIX_H
