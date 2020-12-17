#include "ImageCompressor.h"

//@author Макаревич Дмитрий группа 821702
ImageCompressor::ImageCompressor(const char *path)
{
	//CImg<unsigned char> img("1.bmp");
	this->img = CImg<double> (path);
	this->imgHeight = img.height();
	this->imgWidth = img.width();
	img.display();
	int h = this->imgHeight / this->blockHeight;
	int w = this->imgWidth / this->blockWidth;

	this->X.resize(h * w);

	for (int i = 0; i < (h * w); i++)
	{
		this->X[i].resize(blockHeight * blockWidth * S);
	}
	
	
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			//vector <double> tempVector;
			
			for (int x = 0; x < blockWidth; x++)
			{
				for (int y = 0; y < blockHeight; y++)
				{
					for (int k = 0; k < 3; k++)
					{
						X[i*h + j][(blockWidth * x + y)*S + k] = (2.0 * img(j * blockWidth + y, i * blockHeight + x, 0, k) / 255) - 1;
					}
				}
			}
		}
	}

	initWeightMarix();
	initWeightMarixT();
	
	normalizeWeightMatrix();
	normalizeWeightMatrixT();
	trainNeuralNetwork();

	restoring();

}

//@author Макаревич Дмитрий группа 821702
vector<vector<double>> ImageCompressor::transposeMatrix(vector<double> matrix)
{
	vector <vector <double>> tempMatrix;
	 
	tempMatrix.resize(matrix.size());

	for (int i = 0; i < matrix.size(); i++)
	{
		tempMatrix[i].resize(1);
	}

	/*for (int i = 0; i < matrix.size(); i++)
	{
		tempMatrix[i][0] = matrix[i];
	}*/


	//tempMatrix.resize(matrix[0].size());

	//tempMatrix.push_back(matrix);
	
	return tempMatrix;
}

//@author Макаревич Дмитрий группа 821702
vector<vector<double>> ImageCompressor::transposeMatrix(vector<vector<double>> matrix)
{
	vector <vector <double>> tempMatrix;
	tempMatrix.resize(matrix[0].size());

	for (int i = 0; i < matrix[0].size(); i++)
	{
		tempMatrix[i].resize(matrix.size());
	}

	for (int i = 0; i <tempMatrix.size(); i++)
	{
		for (int j = 0; j < tempMatrix[0].size(); j++)
		{
			tempMatrix[i][j] = matrix[j][i];
		}
	}

	return tempMatrix;
}

//@author Макаревич Дмитрий группа 821702
vector<vector<double>> ImageCompressor::multiplicationMatrix(vector <vector <double>> matrixLeft, vector<vector<double>> matrixRight)
{
	try
	{
		if (matrixLeft[0].size() != matrixRight.size())
		{
			
			cout << matrixLeft[0].size() <<"\t"<< matrixRight.size();
			
			
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

//@author Макаревич Дмитрий группа 821702
vector<vector<double>> ImageCompressor::differenceMatrix(vector<vector<double>> matrixLeft, vector <double> matrixRight)
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

vector<vector<double>> ImageCompressor::differenceMatrix(vector<vector<double>> matrixLeft, vector <vector <double>> matrixRight)
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

//@author Макаревич Дмитрий группа 821702
void ImageCompressor::restoring()
{
	CImg <double> newImg(imgWidth, imgHeight, 1, 3);
	newImg.fill(0);
	vector <vector <double>> result;
	
	int h = this->imgHeight / this->blockHeight;
	int w = this->imgWidth / this->blockWidth;

	//vector<vector <double>> E;
	//E.resize(hiddenLayerSize);
	//for (int i = 0; i < hiddenLayerSize; i++)
	//{
	//	E[i].resize(blockHeight * blockWidth* S);
	//}
		//for (int i = 0; i < hiddenLayerSize; i++)
	//{
	//	for ( int j = 0; j < blockHeight * blockWidth* S; j++)
	//	{
	//		E[i][j] = 1;
	//	}
	//	
	//	//E[i].resize(blockHeight * blockWidth* S);
	//}

	for (int i = 0; i < X.size(); i++)
	{
		result.push_back(toOnedimensionalArray(multiplicationMatrix(multiplicationMatrix(X[i], weightMatrix), weightMatrixT)));

	}

	for (int block = 0; block < X.size(); block++)
	{
		for (int i = 0; i < blockHeight; i++)
		{
			for (int j = 0; j < blockWidth; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					double pixel = (double) 255 * ((result[block][(blockHeight * i + j) * S + k] + 1) / 2.0);///

					if (pixel > 255)
					{
						pixel = 255;
					}
					if (pixel < 0)
					{
						pixel = 0;
					}
					
					newImg(block % h * blockHeight + j, block / w * blockWidth + i, 0, k) = pixel;

				}
			}
		}
	}
	//newImg.save("result.bmp");
	newImg.display();
	//img.display();
}

//@author Макаревич Дмитрий группа 821702
double ImageCompressor::sumMatrix(vector<vector<double>> matrix)
{
	double result = 0;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			result += matrix[i][j] * matrix[i][j];
		}
	}

	return result;
}

//@author Макаревич Дмитрий группа 821702
vector<vector<double>> ImageCompressor::multiplicationMatrix(vector <double> matrixLeft, vector<vector<double>> matrixRight) //перегрузка для ондомерных массивов 
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

	for (int i = 0; i < 1 ; i++)
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

//@author Макаревич Дмитрий группа 821702
void ImageCompressor::trainNeuralNetwork()
{
	int epoch = 0;
	double currentError = maxError + 1;
	vector <vector <double>> Y;
	vector <vector <double>> Xt;
	vector <vector <double>> dX;
	double error = 0;

	while (currentError >= maxError)
	{
		currentError = 0;
		epoch++;
		
		for (int i = 0; i < X.size(); i++)
		{
			Y = multiplicationMatrix(X[i], weightMatrix);
			Xt = multiplicationMatrix(Y, weightMatrixT);
			dX = differenceMatrix(Xt, X[i]); 

			weightMatrix = differenceMatrix(weightMatrix, multiplicationMatrix(alpha, multiplicationMatrix(multiplicationMatrix(transposeMatrix(X[i]), dX), transposeMatrix(weightMatrixT))));
			weightMatrixT = differenceMatrix(weightMatrixT, multiplicationMatrix(alpha, multiplicationMatrix(transposeMatrix(Y), dX)));

			//cout << i << " первый цикл"<<" Эпоха "<< epoch  <<"\n";
		}

		normalizeWeightMatrix();
		normalizeWeightMatrixT();

		//cout << " первый цикл" << " Эпоха " << epoch << "\n";

		for (int i = 0; i < X.size(); i++)
		{
			dX = differenceMatrix(multiplicationMatrix(multiplicationMatrix(X[i], weightMatrix), weightMatrixT), X[i]);
			error = sumMatrix(dX);////
			currentError += error;
		}

		cout << "epoch " << epoch << " Error " << currentError << "\n";
	}
}

//@author Макаревич Дмитрий группа 821702
vector<double> ImageCompressor::toOnedimensionalArray(vector<vector<double>> matrix)
{
	vector <double> tempMatrix;
	
	for (int i = 0; i < matrix[0].size(); i++)
	{
		tempMatrix.push_back(matrix[0][i]);
	}

	return tempMatrix;

}

//@author Макаревич Дмитрий группа 821702
void ImageCompressor::normalizeWeightMatrix()
{
	for (int i = 0; i < hiddenLayerSize; i++)
	{
		double sum = 0;
		for (int j = 0; j <blockHeight * blockWidth * S; j++)
		{
			sum += weightMatrix[j][i] * weightMatrix[j][i];
		}
		sum = sqrt(sum);

		for (int j = 0; j < blockHeight * blockWidth * S; j++)
		{
			weightMatrix[j][i] = weightMatrix[j][i] / sum;
		}
	}
}

//@author Макаревич Дмитрий группа 821702
void ImageCompressor::normalizeWeightMatrixT()
{
	for (int i = 0; i < blockHeight * blockWidth * S; i++)
	{
		double sum = 0;
		for (int j = 0; j < hiddenLayerSize; j++)
		{
			sum += weightMatrixT[j][i] * weightMatrixT[j][i];
		}
		sum = sqrt(sum);

		for (int j = 0; j < hiddenLayerSize; j++)
		{
			weightMatrixT[j][i] = weightMatrixT[j][i] / sum;
		}
	}
}

//@author Макаревич Дмитрий группа 821702
void ImageCompressor::initWeightMarix()
{
	this->weightMatrix.resize(blockHeight * blockWidth * S);

	for (int i = 0; i < blockHeight * blockWidth * S; i++)
	{
		weightMatrix[i].resize(hiddenLayerSize);
	}

	srand(time(0));

	for (int i = 0; i <blockHeight* blockWidth * S ; i++)
	{
		for (int j = 0; j < hiddenLayerSize; j++)
		{			
			weightMatrix[i][j] = (double )(rand()) / RAND_MAX * 2 - 1;
		}
	}

}

//@author Макаревич Дмитрий группа 821702
void ImageCompressor::initWeightMarixT()
{
	weightMatrixT = transposeMatrix(weightMatrix);
}

//@author Макаревич Дмитрий группа 821702
vector <vector <double>> ImageCompressor::multiplicationMatrix(double alpha, vector <vector <double>> matrix)
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
