#include"HopfiledNN.h"


vector<vector<double>> HopfieldNN::multiplicationMatrix(vector<vector<double>> matrixLeft, vector<vector<double>> matrixRight)
{
	try
	{
		if (matrixLeft[0].size() != matrixRight.size())
		{

			cout << matrixLeft[0].size() << "\t" << matrixRight.size();


			throw exception("Cannot miltiplication Matrixes");
		}
	}
	catch (const exception &ex)
	{
		cout << "\n" << "----------------ERORR--------------------" << endl;
		cout << ex.what() << endl;
		cout << "----------------------------------------" << endl;
		system("pause");
	}

	vector <vector <double>> tempMatrix; /// An*m * Bm*k = Cn*k
	tempMatrix.resize(matrixLeft.size());
	for (int i = 0; i < matrixLeft.size(); i++)
	{
		tempMatrix[i].resize(matrixRight[0].size());
	}

	for (int i = 0; i < tempMatrix.size(); i++)
	{
		for (int j = 0; j < tempMatrix[0].size(); j++)
		{
			double temp = 0;

			for (int k = 0; k < matrixRight.size(); k++)
			{
				temp += matrixLeft[i][k] * matrixRight[k][j];
			}

			tempMatrix[i][j] = temp;

		}
	}

	return tempMatrix;
}

vector<vector<double>> HopfieldNN::differenceMatrix(vector<vector<double>> matrixLeft, vector<double> matrixRight)
{
	vector<vector<double>> tempMatrix; // двумерная матрица с одной строкой
	tempMatrix.resize(1);

	for (int i = 0; i < matrixLeft.size(); i++)
	{
		tempMatrix[i].resize(matrixRight.size());
	}

	for (int i = 0; i < matrixLeft[0].size(); i++)
	{
		tempMatrix[0][i] = matrixLeft[0][i] - matrixRight[i];

	}

	return tempMatrix;
}

vector<vector<double>> HopfieldNN::multiplicationMatrix(vector <double> matrixLeft, vector<vector<double>> matrixRight) //перегрузка для ондомерных массивов 
{
	try
	{
		if (matrixLeft.size() != matrixRight.size())
		{
			throw exception("Cannot miltiplication Matrix");
		}
	}
	catch (const exception &ex)
	{
		cout << "\n" << "----------------ERORR--------------------" << endl;
		cout << ex.what() << endl;
		cout << "----------------------------------------" << endl;
		system("pause");
	}
	vector <vector <double >> copyLeftMatrix;
	copyLeftMatrix.push_back(matrixLeft);
	vector <vector <double>> tempMatrix; /// An*m * Bm*k = Cn*k
	tempMatrix.resize(1);

	for (int i = 0; i < 1; i++)
	{
		tempMatrix[i].resize(matrixRight[0].size());
	}

	for (int i = 0; i < tempMatrix.size(); i++)
	{
		for (int j = 0; j < tempMatrix[0].size(); j++)
		{
			double temp = 0;

			for (int k = 0; k < matrixRight.size(); k++)
			{
				temp += copyLeftMatrix[i][k] * matrixRight[k][j];
			}

			tempMatrix[i][j] = temp;

		}
	}

	return tempMatrix;
}

vector<vector<double>> HopfieldNN::multiplicationMatrix(double alpha, vector<vector<double>> matrix)
{
	vector <vector <double>> tempMatrix; /// An*m * Bm*k = Cn*k
	tempMatrix.resize(matrix.size());

	for (int i = 0; i < matrix.size(); i++)
	{
		tempMatrix[i].resize(matrix[0].size());
	}

	for (int i = 0; i < tempMatrix.size(); i++)
	{
		for (int j = 0; j < tempMatrix[0].size(); j++)
		{
			tempMatrix[i][j] = alpha * matrix[i][j];
		}
	}

	return tempMatrix;
}

HopfieldNN::HopfieldNN(const char* pathTrainData, const char* pathTestData)
{
	initWeightMatrix();
	readXandY(pathTrainData,pathTestData);
	trainNeuralNetwork();
	runNeuralNetworkl();
}

void HopfieldNN::initWeightMatrix()
{

	this->weightMatrix.resize(pow(N, 0.5));

	for (int i = 0; i < pow(N, 0.5); i++)
	{
		weightMatrix[i].resize(pow(N, 0.5));
	}

	srand(time(0));

	for (int i = 0; i < pow(N, 0.5); i++)
	{
		for (int j = 0; j < pow(N, 0.5); j++)
		{

			weightMatrix[i][j] = 0;
			//weightMatrix[i][j] = (double)(rand()) / RAND_MAX * 2 - 1;
		}
	}
}

vector<vector<double>> HopfieldNN::sumMatrix(vector<vector<double>> matrixLeft, vector<vector<double>> matrixRight)
{
	vector<vector<double>> tempMatrix;

	tempMatrix.resize(matrixLeft.size());
	for (int i = 0; i < matrixLeft.size(); i++)
	{
		tempMatrix[i].resize(matrixRight[0].size());
	}


	for (int i = 0; i < matrixLeft.size(); i++)
	{
		for (int j = 0; j < matrixLeft[0].size(); j++)
		{
			tempMatrix[i][j] = matrixLeft[i][j] + matrixRight[i][j];
		}
	}

	return tempMatrix;
}

vector<vector<double>> HopfieldNN::vectorToMatrix(vector<double> tempVector)
{
	vector<vector<double>> tempMatrix;

	tempMatrix.push_back(tempVector);
	
	return tempMatrix;
}



vector<vector<double>> HopfieldNN::differenceMatrix(vector<vector<double>> matrixLeft, vector <vector <double>> matrixRight)
{
	vector<vector<double>> tempMatrix;

	tempMatrix.resize(matrixLeft.size());
	for (int i = 0; i < matrixLeft.size(); i++)
	{
		tempMatrix[i].resize(matrixRight[0].size());
	}


	for (int i = 0; i < matrixLeft.size(); i++)
	{
		for (int j = 0; j < matrixLeft[0].size(); j++)
		{
			tempMatrix[i][j] = matrixLeft[i][j] - matrixRight[i][j];
		}
	}

	return tempMatrix;
}

vector<vector<double>> HopfieldNN::transposeMatrix(vector<vector<double>> matrix)
{
	vector <vector <double>> tempMatrix;
	tempMatrix.resize(matrix[0].size());

	for (int i = 0; i < matrix[0].size(); i++)
	{
		tempMatrix[i].resize(matrix.size());
	}

	for (int i = 0; i < tempMatrix.size(); i++)
	{
		for (int j = 0; j < tempMatrix[0].size(); j++)
		{
			tempMatrix[i][j] = matrix[j][i];
		}
	}

	return tempMatrix;
}

vector<vector<double>> HopfieldNN::transposeMatrix(vector<double> matrix)
{
	vector <vector <double>> tempMatrix;

	tempMatrix.resize(matrix.size());

	for (int i = 0; i < matrix.size(); i++)
	{
		tempMatrix[i].resize(1);
	}

	for (int i = 0; i < matrix.size(); i++)
	{
		tempMatrix[i][0] = matrix[i];
	}

	return tempMatrix;
}

void HopfieldNN::readXandY(const char* pathTrainData, const char* pathTestData)
{
	ifstream fin;
	fin.exceptions(ifstream::badbit | ifstream::failbit);
	
	try
	{
		fin.open(pathTrainData);
	}
	catch (const std::exception& ex)
	{
		//ex.what();
		cout << "Файл не был открыт!" << endl;
	}

	fin.is_open();

	X.resize(imageNumber);

	for (int i = 0; i < imageNumber; i++)
	{
		X[i].resize(N);
	}

	for (int i = 0; i < imageNumber; i++)
	{
		char temp;

		if (pathTestData == "test1.txt")
		{
			cout << "Образ номер" << i + 1 << "\n";
		}

		for (int j = 0; j < N; j++)
		{
			
			fin >> temp;
			
			if (j % int (pow(N, 0.5)) == 0 && j!=0 && pathTestData == "test1.txt")
			{
				cout << "\n";
			}

			if (pathTestData == "test1.txt")
			{
				cout << temp;
			}

			if (temp == '@')
			{
				X[i][j] = 1;
			}

			if (temp == '*')
			{
				X[i][j] = -1;
			}

		}

		//fin >> temp;
		if (pathTestData == "test1.txt")
		{
			cout << "\n";
			cout << "\n";
		}
	}

	fin.close();
	try
	{
		fin.open(pathTestData);
	}
	catch (const std::exception&)
	{
		cout << "Файл не был открыт!" << endl;
	}
	

	Y.resize(imageNumber);

	for (int i = 0; i < imageNumber; i++)
	{
		Y[i].resize(N);
	}

	//for (int i = 0; i < imageNumber; i++)
	//{
		
	cout  << "Фигура с шумом" << "\n";
	
	char temp;

		for (int j = 0; j < N; j++)
		{

			fin >> temp;

			if (j % int(pow(N, 0.5)) == 0 && j != 0)
			{
				cout << "\n";
			}

			cout << temp;

			if (temp == '@')
			{
				Y[0][j] = 1;
			}

			if (temp == '*')
			{
				Y[0][j] = -1;
			}

		}

	fin.close();
}

vector<vector<double>> HopfieldNN::findBackMatrix(vector<vector<double>> matrix)
{
	//void inversion(double **A, int N)
	//{
		double temp;

		double **E = new double *[matrix.size()];

		for (int i = 0; i < matrix.size(); i++)
			E[i] = new double[matrix.size()];

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix.size(); j++)
			{
				E[i][j] = 0.0;

				if (i == j)
					E[i][j] = 1.0;
			}

		for (int k = 0; k < matrix.size(); k++)
		{
			temp = matrix[k][k];

			for (int j = 0; j < matrix.size(); j++)
			{
				matrix[k][j] /= temp;
				E[k][j] /= temp;
			}

			for (int i = k + 1; i < matrix.size(); i++)
			{
				temp = matrix[i][k];

				for (int j = 0; j < matrix.size(); j++)
				{
					matrix[i][j] -= matrix[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int k = matrix.size() - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = matrix[i][k];

				for (int j = 0; j < matrix.size(); j++)
				{
					matrix[i][j] -= matrix[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix.size(); j++)
				matrix[i][j] = E[i][j];

		for (int i = 0; i < matrix.size(); i++)
			delete[] E[i];

		delete[] E;
	//}

		return matrix;

}

double HopfieldNN:: hyperbolicTangent(double x) { // не подходит эта функция так как она не непрерывная 
	
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
	
	
	/*if (x > 0)
		return 1;
	else if (x <= 0)
		return -1;*/
}


void HopfieldNN::trainNeuralNetwork()
{
	//weightMatrix = multiplicationMatrix(multiplicationMatrix(X, findBackMatrix(multiplicationMatrix(transposeMatrix(X), X))), transposeMatrix(X)); // метод проекций 
	weightMatrix = multiplicationMatrix(multiplicationMatrix(transposeMatrix(X), findBackMatrix(multiplicationMatrix(X, transposeMatrix(X)))), X);
	/*for (int i = 0; i < pow(N, 0.5); i++) // метод хебба
	{
		weightMatrix = sumMatrix(weightMatrix,multiplicationMatrix(transposeMatrix(X[i]),vectorToMatrix(X[i])));
	}*/
	
	weightMatrix = multiplicationMatrix(/*1 /*/ N, weightMatrix);// нормализация весов 

	for (int i = 0; i < pow(N, 0.5); i++)// зануление главной диагонали 
	{
		weightMatrix[i][i] = 0;
	}
}

void HopfieldNN::runNeuralNetworkl()
{
	vector <vector <double>> result;
	//result.resize(1);
	//result[0].resize(N, 0);

	vector <vector <double>> tempVector;
	vector <vector <double>> tempPreviosVector;
	tempVector.resize(1);
	tempVector[0].resize(N, 0);

	tempPreviosVector.resize(1);
	tempPreviosVector[0].resize(N, 0);

	 double currentError = 0;

	 double PrevioustError = 0;

	 int iteration = 0;

	// result = vectorToMatrix(Y[0]);
	 result.push_back(Y[0]);
	  
	do
	{
		currentError = 0;
		tempPreviosVector = result;
		
		//result = transposeMatrix(multiplicationMatrix(weightMatrix, transposeMatrix(result)));
		result = multiplicationMatrix(result, weightMatrix);

		for (int i = 0; i < result[0].size(); i++) // прогон через функцию 
		{
			result[0][i] = hyperbolicTangent(result[0][i]);
		}

		for (int i = 0; i < result[0].size(); i++)
		{
			currentError += pow(result[0][i] - tempVector[0][i], 2);
			//PrevioustError += pow(result[0][i] - tempPreviosVector[0][i], 2);
		}

		tempVector = result;

		iteration++;

	} while (currentError > E /*&& PrevioustError > E */ && iteration < maxIteration);

	int answer = 99;
	
	int imageCounter = imageNumber; // блок проверки результат на совпадение 
	for (int i = 0 ; i < imageCounter; i++)
	{
		int coincidence = 0;
		for (int j = 0; j < N; j++)
		{
			if ( abs(result[0][j] - X[i][j]) < koefficient)
			{
				coincidence++;
			}
		}
		if (coincidence == N)
		{
			answer = i;
			break;
		}
	}

	if (answer != 99)
	{
		cout << "\n" << "Зашумленный образ равен образу " << ++answer << "\n\n\n";
	}
	else
	{
		cout << "\n" << "Модель не смогла определить образ" << "\n\n\n";
	}
}
