#include"jordanElman.h"

JordanElmanModel::JordanElmanModel()
{

	

	/*sequence = calPeriodicFunction(k);
	initMatrixes(sequence);
	sequence = calPeriodicFunction(k + r);
	trainNeuralNetwork();
	runNeuralNetworkl();*/

	alpha = 0.000001;

	//sequence = calFibonacciNumbers(k);
	//initMatrixes(sequence);
	//sequence = calFibonacciNumbers(k + r);
	//trainNeuralNetwork();
	//runNeuralNetworkl();
	 
	

	/*sequence = calPowerFunction(k);
	initMatrixes(sequence);
	sequence = calPowerFunction(k + r);
	trainNeuralNetwork();
	runNeuralNetworkl();*/

	alpha = 0.000001;
	maxError = 0.0000001;

	sequence = calArithmeticProgression(k);
	initMatrixes(sequence);
	sequence = calArithmeticProgression(k + r);
	trainNeuralNetwork();
	runNeuralNetworkl();


	alpha = 0.000000001;

	p = 4;
	k = 5;
	m = k - p;
	
	/*sequence = calFactorialNumbers(k);
	initMatrixes(sequence);
	sequence = calFactorialNumbers(k + r);
	trainNeuralNetwork();
	runNeuralNetworkl();*/

	/*fibonacciSequnce =  calFibonacciNumbers(k);
	periodicSequnce = calPeriodicFunction(k);
	powerSequnce =  calPowerFunction(k);*/
	
	/*expFibonacciSequnce = calFibonacciNumbers(k + r);
	expPeriodicSequnce = calPeriodicFunction(k + r);
	expPowerSequnce = calPowerFunction(k + r);*/
}

vector<vector<double>> JordanElmanModel::transposeMatrix(vector<vector<double>> matrix)
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

vector<vector<double>> JordanElmanModel::transposeMatrix(vector<double> matrix)
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


	//tempMatrix.resize(matrix[0].size());

	//tempMatrix.push_back(matrix);

	return tempMatrix;
}



void JordanElmanModel::initWeightMatrixT()
{
	this->weightMatrixT.resize(m);

	for (int i = 0; i < m; i++)
	{
		weightMatrixT[i].resize(1);
	}

	srand(time(0));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			weightMatrixT[i][j] = (double)(rand()) / RAND_MAX * 2 - 1;
		}
	}
}

void JordanElmanModel::initWeightContextMatrixOut_Hid()
{
	this->weightContextMatrixOut_Hid.resize(1);

	for (int i = 0; i < 1; i++)
	{
		weightContextMatrixOut_Hid[i].resize(m);
	}

	srand(time(0));

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			weightContextMatrixOut_Hid[i][j] = (double)(rand()) / RAND_MAX * 2 - 1;
		}
	}
}

void JordanElmanModel::runNeuralNetworkl()
{
	resSequence.clear();

	int j = k - p;
	for (int i = 0; i < p; i++)
	{
		input[i] = sequence[j];
		j++;
	}


	vector<double> tempVector;
	tempVector.resize(contextHiddenLayer.size(), 0);

	contextHiddenLayer = tempVector;

	contextOututLayer = 0;
		


	for (int i = 0; i < r; i++)
	{
		if (i > 0)
		{
			for (int j = 0; j < p - 1; j++)
			{
				input[j] = input[j + 1];
			}
			input[p - 1] = output;


		}

		vector<vector <double>> inputSum; // 1 * m
		vector<vector <double>> hiddenContextSum;  // 1 * m 
		vector<vector <double>> outputContextSum; // 1 * m 
		vector<vector <double>> hiddenLayerValues; // 1 * m 

		vector<vector <double>> outputLayerValues; // 1*1

				inputSum = multiplicationMatrix(input, weightMatrix); // 1 * m
				hiddenContextSum = multiplicationMatrix(contextHiddenLayer, weightContextMatrixPr_Hid); // 1 * m
				outputContextSum = multiplicationMatrix(contextOututLayer, weightContextMatrixOut_Hid); // 1 * m

				hiddenLayerValues = sumMatrix(sumMatrix(inputSum, hiddenContextSum), outputContextSum); // значение которое пришло к нейрону 

				hiddenLayerValues = differenceMatrix(hiddenLayerValues, T);// пороговое значение

				for (int k = 0; k < m; k++) // прогон для значенией нейроновчерез функцию активации
				{
					hiddenLayerValues[0][k] = actFunc(hiddenLayerValues[0][k]);
				}

				outputLayerValues = multiplicationMatrix(hiddenLayerValues, weightMatrixT); // число кторое приходит на последний нейрон 

				outputLayerValues[0][0] = outputLayerValues[0][0] - T_;

				outputLayerValues[0][0] = actFunc(outputLayerValues[0][0]);

				contextHiddenLayer = toOnedimensionalArray(hiddenLayerValues); // записываем к контекстыый слой из скрытого слоя  

				contextOututLayer = outputLayerValues[0][0]; // выходные значения записываем в контекст 

			//	currentError += pow(outputLayerValues[0][0] - expValues[i], 2) / 2; 

				output = outputLayerValues[0][0];

				resSequence.push_back(output);

		//	}

	}

	
	cout << "Result sequence: \n";
	for (int i = 0; i < r; i++)
	{

		cout << "Result: " << resSequence[i] << "  Expected value: " << sequence[k + i] << "  Line error: " << sequence[k + i] - resSequence[i] << endl;
	}


}

vector<vector<double>> JordanElmanModel::sumMatrix(vector<vector<double>> matrixLeft, vector<vector<double>> matrixRight)
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

void JordanElmanModel::trainNeuralNetwork()
{
	double currentError;
	int epoch=0;

	vector<vector <double>> inputSum; // 1 * m
	vector<vector <double>> hiddenContextSum;  // 1 * m 
	vector<vector <double>> outputContextSum; // 1 * m 
	vector<vector <double>> hiddenLayerValues; // 1 * m 

	vector<vector <double>> outputLayerValues; // 1*1
	

	do {
		epoch++;
		currentError = 0;

		vector<double> tempVector;
		tempVector.resize(contextHiddenLayer.size(), 0);

		contextHiddenLayer = tempVector;

		contextOututLayer = 0; 

		for (int i = 0; i < m; i++)
		{

			inputSum = multiplicationMatrix(X[i], weightMatrix); // 1 * m 
			hiddenContextSum = multiplicationMatrix(contextHiddenLayer, weightContextMatrixPr_Hid); // 1 * m
			outputContextSum = multiplicationMatrix(contextOututLayer, weightContextMatrixOut_Hid); // 1 * m
			
			hiddenLayerValues = sumMatrix(sumMatrix(inputSum, hiddenContextSum), outputContextSum); // значение которое пришло к нейрону 

			hiddenLayerValues = differenceMatrix(hiddenLayerValues, T);// пороговое значение

			for (int k = 0; k <m ; k++) // прогон для значенией нейроновчерез функцию активации
			{
				hiddenLayerValues[0][k] = actFunc(hiddenLayerValues[0][k]);
			}

			outputLayerValues = multiplicationMatrix(hiddenLayerValues, weightMatrixT); // число кторое приходит на последний нейрон 

			outputLayerValues[0][0] = outputLayerValues[0][0] - T_;

			outputLayerValues[0][0] = actFunc(outputLayerValues[0][0]);

			contextHiddenLayer =  toOnedimensionalArray(hiddenLayerValues); // записываем к контекстыый слой из скрытого слоя  

			contextOututLayer = outputLayerValues[0][0]; // выходные значения записываем в контекст 

		//	currentError += pow(outputLayerValues[0][0] - expValues[i], 2) / 2; 

			output = outputLayerValues[0][0];


			// обратное распространение ошибки

			vector <vector<double>> dX;
			
			dX.resize(1);
			dX[0].resize(1);

			dX[0][0] = output - expValues[i];


			weightMatrix = differenceMatrix(weightMatrix, multiplicationMatrix(alpha, multiplicationMatrix(multiplicationMatrix(transposeMatrix(X[i]), dX), transposeMatrix(weightMatrixT))));

			weightContextMatrixPr_Hid = differenceMatrix(weightContextMatrixPr_Hid, multiplicationMatrix(alpha, multiplicationMatrix(multiplicationMatrix(transposeMatrix(contextHiddenLayer), dX), transposeMatrix(weightMatrixT))));

			weightContextMatrixOut_Hid = differenceMatrix(weightContextMatrixOut_Hid, multiplicationMatrix(alpha, multiplicationMatrix(multiplicationMatrix(contextOututLayer, dX), transposeMatrix(weightMatrixT))));


			weightMatrixT = differenceMatrix(weightMatrixT, multiplicationMatrix(alpha, multiplicationMatrix(transposeMatrix(hiddenLayerValues), dX)));

			T = multiplicationMatrix(alpha,multiplicationMatrix(dX, transposeMatrix(weightMatrixT))); // 1*m

			T_ = alpha* dX[0][0];
		

		}


		vector<double> tempVector2;
		tempVector2.resize(contextHiddenLayer.size(), 0);

		contextHiddenLayer = tempVector2;

		contextOututLayer = 0; 

		for (int i = 0; i < m; i++)
		{
			inputSum = multiplicationMatrix(X[i], weightMatrix); // 1 * m
			hiddenContextSum = multiplicationMatrix(contextHiddenLayer, weightContextMatrixPr_Hid); // 1 * m
			outputContextSum = multiplicationMatrix(contextOututLayer, weightContextMatrixOut_Hid); // 1 * m

			hiddenLayerValues = sumMatrix(sumMatrix(inputSum, hiddenContextSum), outputContextSum); // значение которое пришло к нейрону 

			for (int k = 0; k < m; k++) // прогон для значенией нейроновчерез функцию активации
			{
				hiddenLayerValues[0][k] = actFunc(hiddenLayerValues[0][k]);
			}

			outputLayerValues = multiplicationMatrix(hiddenLayerValues, weightMatrixT); // число кторое приходит на последний нейрон 

			outputLayerValues[0][0] = actFunc(outputLayerValues[0][0]);

			contextHiddenLayer = toOnedimensionalArray(hiddenLayerValues); // записываем к контекстыый слой из скрытого слоя  

			contextOututLayer = outputLayerValues[0][0]; // выходные значения записываем в контекст 

			currentError += pow(outputLayerValues[0][0] - expValues[i], 2) / 2;

			output = outputLayerValues[0][0];
		}

		if (epoch <= 10 || epoch % 10000 == 0)
		{
			cout << "Epoch " << epoch << " Error: " << currentError << endl;
		}

	} while (currentError > maxError && epoch < N); ////

}

vector<double> JordanElmanModel::toOnedimensionalArray(vector<vector<double>> matrix)
{
	vector <double> tempMatrix;

	for (int i = 0; i < matrix[0].size(); i++)
	{
		tempMatrix.push_back(matrix[0][i]);
	}

	return tempMatrix;
}

double JordanElmanModel::actFunc(double x)
{
	return  x;
}

double JordanElmanModel::derivativeActFunc(double value)
{
	return 1;
}

vector<double> JordanElmanModel::calFibonacciNumbers(int number)
{
	vector<double> tempVector;
	tempVector.push_back(0);
	tempVector.push_back(1);

	for (int i = 1; i < number - 1 ; i++)
	{
		tempVector.push_back(tempVector[i] + tempVector[i-1]);
	}

	return tempVector;
}

vector<double> JordanElmanModel::calFactorialNumbers(int number)
{
	vector<double> tempVector;
	int prev = 1;

	for (int i = 1; i <= number; i++)
	{
		tempVector.push_back(prev * i);

		 prev = i * prev;
	}

	return tempVector;
}

vector<double> JordanElmanModel::calPeriodicFunction(int number)
{
	vector<double> tempVector;
	
	for (int i = 0; i < number; i++)
	{
		switch (i % 4)
		{
			case 0:
			{
				tempVector.push_back(0);
				break;
			}

			case 1:
			{
				tempVector.push_back(1);
				break;
			}

			case 2:
			{
				tempVector.push_back(0);
				break;
			}

			case 3:
			{
				tempVector.push_back(-1);
				break;
			}


			default:
				break;
		}
	}

	return tempVector;
}

vector<double> JordanElmanModel::calPowerFunction(int number)
{
	vector<double> tempVector;

	for (int i = 1; i <= number; i++)
	{
		tempVector.push_back(pow(i, 2));
	}


	return tempVector;
}

vector<double> JordanElmanModel::calArithmeticProgression(int number)
{
	vector<double> tempVector;

	for (int i = 1; i <= number; i++)
	{
		tempVector.push_back(i*2);
	}


	return tempVector;

}

void JordanElmanModel::initMatrixes(vector <double> sequnce)
{
	initWeightMatrix();
	initWeightMatrixT();
	initWeightContextMatrixOut_Hid();
	initWeightContextMatrixPr_Hid();

	expValues.clear();

	input.resize(p, 0);

	hidden.resize(m, 0);
	output = 0;
	contextHiddenLayer.resize(m, 0);
	contextOututLayer = 0;

	T_ = 0;
	T.resize(1);

	for (int i = 0; i < 1; i++)
	{
		T[i].resize(m);
	}

	X.resize(m);


	for (int i = 0; i < m; i++)
	{
		X[i].resize(p);
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			X[i][j] = sequnce[i + j];
		}

		expValues.push_back(sequnce[i + p]);
		/////////////////////
	}
}

vector<vector<double>> JordanElmanModel::multiplicationMatrix(vector<vector<double>> matrixLeft, vector<vector<double>> matrixRight)
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

vector<vector<double>> JordanElmanModel::differenceMatrix(vector<vector<double>> matrixLeft, vector<double> matrixRight)
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

vector<vector<double>> JordanElmanModel::multiplicationMatrix(vector <double> matrixLeft, vector<vector<double>> matrixRight) //перегрузка для ондомерных массивов 
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

vector<vector<double>> JordanElmanModel::multiplicationMatrix(double alpha, vector<vector<double>> matrix)
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

void JordanElmanModel::initWeightMatrix()
{

	this->weightMatrix.resize(p);

	for (int i = 0; i < p; i++)
	{
		weightMatrix[i].resize(m);
	}

	srand(time(0));

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < m; j++)
		{
			weightMatrix[i][j] = (double)(rand()) / RAND_MAX * 2 - 1;
		}
	}
}

vector<vector<double>> JordanElmanModel::differenceMatrix(vector<vector<double>> matrixLeft, vector <vector <double>> matrixRight)
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


void JordanElmanModel::initWeightContextMatrixPr_Hid()
{

	this->weightContextMatrixPr_Hid.resize(m);

	for (int i = 0; i < m; i++)
	{
		weightContextMatrixPr_Hid[i].resize(m);
	}

	srand(time(0));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			weightContextMatrixPr_Hid[i][j] = (double)(rand()) / RAND_MAX * 2 - 1;
		}
	}
}
