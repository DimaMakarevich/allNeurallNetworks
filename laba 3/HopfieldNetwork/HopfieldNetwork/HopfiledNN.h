
#include<iostream>
#include "String"
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
//#include <ofstream>

//@author ћакаревич ƒмитрий группа 821702

using namespace std;

class HopfieldNN
{
public:

	HopfieldNN(const char* pathTrainData, const char* pathTestData);

//private:
public:

	vector<vector <double>> weightMatrix;
	void initWeightMatrix();
	
	vector <vector <double>> transposeMatrix(vector <vector <double>> matrix);
	vector <vector <double>> transposeMatrix(vector <double> matrix);
	void readXandY(const char* pathTrainData, const char* pathTestData);
	vector <vector<double>> findBackMatrix(vector <vector <double>> matrix); // метод элементарных преобразований
	vector<vector <double>> X;
	vector<vector <double>> Y;

	vector <vector <double>> multiplicationMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);
	vector <vector <double>> differenceMatrix(vector <vector <double>> matrixLeft, vector <double> matrixRight);
	vector <vector <double >> multiplicationMatrix(vector <double> matrixLeft, vector <vector <double>> matrixRight);
	vector <vector <double>> multiplicationMatrix(double alpha, vector <vector <double>> matrix);
	vector <vector <double>> differenceMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);
	vector <vector <double>> sumMatrix(vector <vector <double>> matrixLeft, vector <vector <double>> matrixRight);

	vector<vector<double>> vectorToMatrix(vector<double> tempVector);

	double hyperbolicTangent(double x);

	void trainNeuralNetwork();
	void runNeuralNetworkl();
	double E = 0.000001;
	int N = 100;
	int imageNumber= 5;
	int maxIteration = 10;
	double koefficient = 0.0001;// так как у нашей системы непрепывное состоние то значение совпадать будет не точно а приблизно коеф показывает допустимое расхождение 
	
};


