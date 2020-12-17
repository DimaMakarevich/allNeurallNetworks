#pragma once

#include<iostream>
#include "String"
#include <vector>
#include <random>
#include <ctime>

//@author ��������� ������� ������ 821702

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
	vector<vector <double>> X; // m * p ������ 

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
	
	int p = 18; // ���������� ������� � ������� �������� 
	int k = 20;  // ����������� ��������� ������������������  // 11 � 15 ��� ������������� �������
	int m = k - p; // L= m  ���������� ����� � ������� ��������  � ����� �������� � ������� ���� 

	double maxError = 0.00000001;
	double N = 1000000; // ������������ ���������� ��������
	double alpha = 0.0001; //
	int r = 2; // ���������� ��������������� ��������� 


	vector <double> input; // ������� ������ (p)
	vector <double> hidden; // �������� ������ �� �������� ����
	double output; // �� ��������� ����
	vector <double> contextHiddenLayer; // �������� ������� ���� 
	double contextOututLayer; // �������� ��������� ���� 
	
}; 