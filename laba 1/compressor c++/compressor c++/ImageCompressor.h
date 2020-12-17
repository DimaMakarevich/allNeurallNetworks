#pragma once
#include "CImg-2.4.1\CImg.h"
#include<iostream>
#include <String>
#include <vector>
#include <random>

//@author Макаревич Дмитрий группа 821702

using namespace cimg_library;
using namespace std;


class ImageCompressor
{
public:
	ImageCompressor(const char* path);
	//show();

private:
	vector <vector <double>> transposeMatrix(vector <vector <double>> matrix);
	vector <vector <double>> transposeMatrix(vector <double> matrix);
	vector<vector <double>> weightMatrix;
	vector<vector <double>> weightMatrixT;
	vector <vector <double>> multiplicationMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);
	vector <vector <double>> differenceMatrix(vector <vector <double>> matrixLeft, vector <double> matrixRight);
	vector <vector <double >> multiplicationMatrix(vector <double> matrixLeft, vector <vector <double>> matrixRight);
	vector <vector <double>> multiplicationMatrix(double alpha, vector <vector <double>> matrix);
	vector <vector <double>> differenceMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);
	void restoring();
	double sumMatrix(vector <vector <double>> matrix);
	void trainNeuralNetwork();
	vector <double> toOnedimensionalArray(vector <vector <double>> matrix);
	void normalizeWeightMatrix();
	void normalizeWeightMatrixT();
	void initWeightMarix();
	 void initWeightMarixT();
	int blockHeight = 8;
	int blockWidth = 8;
	int imgWidth;
	int imgHeight;
	double maxError = 5000;
	double alpha = 0.007; //7
	int S = 3;// scale
	int hiddenLayerSize = 32; /// p<= 2 * blockHeight * blockWidth * S \32
	vector<vector <double>> X; // 
	CImg <double > img;
};