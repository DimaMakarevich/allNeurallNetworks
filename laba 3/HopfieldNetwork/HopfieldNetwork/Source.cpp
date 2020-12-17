#include<iostream>
#include"HopfiledNN.h"



using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");


	//vector<vector<double>> X = {{1,2,3 }, {6, 3, 1}, {7, 4, 10}};
	//vector<vector<double>> Y;
	
	//HopfieldNN("C:\\Users\\NotePad\\Desktop\\'sem 5'\\MRZVIS\\'laba 3'\\HopfieldNetwork\\HopfieldNetwork\\1.txt", "test1.txt");
	HopfieldNN bb("train.txt", "test1.txt");
	
	HopfieldNN("train.txt", "test2.txt");
	HopfieldNN("train.txt", "test3.txt");
	HopfieldNN("train.txt", "test4.txt");
	HopfieldNN("train.txt", "test5.txt");
	//Y= nn.multiplicationMatrix(X, nn.findBackMatrix(X));
	/*vector<vector<int>> v = {
		{ 1, 2, 3, 4, 5 },
		{ 6, 7, 8, 9, 0 }
	};*/
	
	system("pause");
	return 0;
}