#pragma once
#include <fstream>
#include <vector>
using namespace std;

class SecondTask {
private:
	int n, m, k;
	string path = "GeneratedMatrix.txt";
	ifstream fin1, fin2;
	vector <vector <int>> matrix1, matrix2, resultMatrix;
public:
	SecondTask(int n, int m, int k);
	bool OpenFileForReading();
	ifstream& GotoLine(ifstream& file, unsigned int num);
	void ReadMatrix(ifstream& file, vector<vector<int>> &matrix);
	void ReadInputMatrices();
	vector<int> multiplyRowToMatrix(vector<int> &row);
 	void ParallelNaiveAlgorithm();
	int measureTimeForAlgo();
	bool checkResultMatrix();
	void closeFile();
};