#include <iostream>
#include "SecondTask.h"
#include "Stopwatch.h"
#include "MatrixMultiplication.h"
#include <thread>
#include <limits>
#include <functional>

using namespace std;

SecondTask::SecondTask(int n, int m, int k)
{
    this->n = n;
    this->m = m;
    this->k = k;

    matrix1.resize(n);
    for (int i = 0; i < n; ++i) {
        matrix1[i].resize(m);
    }

    matrix2.resize(m);
    for (int i = 0; i < m; ++i) {
        matrix2[i].resize(k);
    }

    resultMatrix.resize(n);
}

bool SecondTask::OpenFileForReading()
{
    fin1.open(path);
    fin2.open(path);

    if (!fin1.is_open() || !fin2.is_open())
    {
        cout << "Cannot open the file for reading" << endl;
        fin1.close();
        fin2.close();
        return false;
    }
}

ifstream& SecondTask::GotoLine(ifstream& file, unsigned int num) {
    file.seekg(ios::beg);
    for (int i = 0; i < (num - 1); ++i) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return file;
}

void SecondTask::ReadMatrix(ifstream& file, vector<vector<int>> &matrix)
{
    int element = 0;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            file >> element;
            matrix[i][j] = element;
        }
    }
}

void SecondTask::ReadInputMatrices() {
    vector <thread> threads(2);

    for (int i = 0; i < threads.size(); ++i) {
        switch (i) {
        case 0:
            GotoLine(fin1, 2);
            threads[i] = thread(&SecondTask::ReadMatrix, this, ref(fin1), ref(matrix1));
            break;
        case 1:
            GotoLine(fin2, n + 3);
            threads[i] = thread(&SecondTask::ReadMatrix, this, ref(fin2), ref(matrix2));
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

vector<int> SecondTask::multiplyRowToMatrix(vector<int> &row) {
    vector <int> result(k);

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i] += row[j] * matrix2[j][i];
        }            
    }

    return result;
}

void SecondTask::ParallelNaiveAlgorithm()
{
    ReadInputMatrices();

    vector <thread> threads(n);

    for (int i = 0; i < n; ++i) {
        threads[i] = thread([this, i]()
            {             
                resultMatrix[i] = multiplyRowToMatrix(matrix1[i]);
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

int SecondTask::measureTimeForAlgo()
{
    Stopwatch stopwatch;

    stopwatch.start();

    ParallelNaiveAlgorithm();

    auto elapsedTime = stopwatch.stop();

    return elapsedTime.count();
}

bool SecondTask::checkResultMatrix() {
    int matrixElementFromFile;

    GotoLine(fin1, (n + m + 4));

    for (int i = 0; i < resultMatrix.size(); ++i) {
        for (int j = 0; j < resultMatrix[0].size(); ++j) {
            fin1 >> matrixElementFromFile;
            if (resultMatrix[i][j] != matrixElementFromFile)
            {
                cout << "Dot product doesn't match at a[" << i << "][" << j << "]";
                return false;
            }
        }
    }

    return true;
}

void SecondTask::closeFile()
{
    fin1.close();
    fin2.close();
}