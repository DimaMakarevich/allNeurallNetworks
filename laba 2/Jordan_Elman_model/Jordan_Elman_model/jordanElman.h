#pragma once

#include<iostream>
#include "String"
#include <vector>
#include <random>
#include <ctime>

//@author Макаревич Дмитрий группа 821702

using namespace std;


class JordanElmanModel
{
public:
	JordanElmanModel();
	//show();

private:
	vector <vector <double>> transposeMatrix(vector <vector <double>> matrix);
	vector <vector <double>> transposeMatrix(vector <double> matrix);

	vector<vector <double>> weightMatrix;
	vector<vector <double>> weightMatrixT;
	vector<vector <double>> weightContextMatrixPr_Hid;
	vector<vector <double>> weightContextMatrixOut_Hid;
	vector<vector <double>> X; // m * p размер 

	void initWeightMatrix();
	void initWeightContextMatrixPr_Hid();
	void initWeightMatrixT();
	void initWeightContextMatrixOut_Hid();

	vector <double> calFibonacciNumbers(int number);
	vector <double> calFactorialNumbers(int number);
	vector <double> calPeriodicFunction(int number);
	vector <double> calPowerFunction(int number);
	vector <double> calArithmeticProgression(int number);

	vector<double> sequence;;

	vector<double> expSequence;
	vector<double> resSequence;


	vector <double> expValues;

	vector  <vector<double>> T;
	double T_;

	void initMatrixes(vector <double> sequnce); 

	vector <vector <double>> multiplicationMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);
	vector <vector <double>> differenceMatrix(vector <vector <double>> matrixLeft, vector <double> matrixRight);
	vector <vector <double >> multiplicationMatrix(vector <double> matrixLeft, vector <vector <double>> matrixRight);
	vector <vector <double>> multiplicationMatrix(double alpha, vector <vector <double>> matrix);
	vector <vector <double>> differenceMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);

	void runNeuralNetworkl();

	vector <vector <double>> sumMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);
	void trainNeuralNetwork();
	vector <double> toOnedimensionalArray(vector <vector <double>> matrix);
	//void normalizeWeightMatrix();
	//void normalizeWeightMatrixT();
	double actFunc(double x);
	double derivativeActFunc(double value);
	
	int p = 18; // количетсво стобцов в матрице обучения 
	int k = 20;  // размерность обучаемой последовательности  // 11 и 15 для показаетльной функции
	int m = k - p; // L= m  количетсво строк в матрице обучения  и колво нейронов в скрытом слое 

	double maxError = 0.00000001;
	double N = 1000000; // максимальное количетсво итераций
	double alpha = 0.0001; //
	int r = 2; // количетсов предсказываемых элементов 


	vector <double> input; // входной вектор (p)
	vector <double> hidden; // выходной вектор из скрытого слоя
	double output; // из выходного слоя
	vector <double> contextHiddenLayer; // контекст скрытго слоя 
	double contextOututLayer; // контекст выходного слоя 
	
}; 