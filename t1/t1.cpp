// t1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include "Stopwatch.h"
#include "MatrixMultiplication.h"
#include "FirstTask.h"
#include <algorithm>
#include "SecondTask.h"

using namespace std;

class RunProgram
{
private:
    int n, m, k;
    int maxValue;
    bool success;
public:
    RunProgram()
    {
        do {
        cout << "Input matrix dimension n, m, k: ";
        cin >> this->n >> this->m >> this->k;

        cout << "Input max value of matrix: "; 
        cin >> this->maxValue;
        } while (!ValidatorForDimensions());
    }

    bool ValidatorForDimensions()
    {
        if (n <= 0 || m <= 0 || k <= 0)
        {
            cout << "Wrong n, m, k" << endl;
            return false;
        }
    }

    bool runFirstTask() {
        FirstTask test = FirstTask(n, m, k, maxValue);

        success = test.OpenFileForWriting();
        if (!success) return false;

        cout << "Time taken by iterative naive algorithm: " << test.measureTimeForAlgo() << " millisec" << endl;

        test.closeFile();
    }

    bool runSecondTask() {
        SecondTask test2 = SecondTask(n, m, k);

        success = test2.OpenFileForReading();
        if (!success) return false;

        cout << "Time taken by parallel naive algorithm: " << test2.measureTimeForAlgo() << " millisec" << endl;
        if (test2.checkResultMatrix()) {
            cout << "Result matricies are identical" << endl;
        }

        test2.closeFile();
    }
};

int main()
{
    srand(time(NULL));

    RunProgram go = RunProgram();

    if (!go.runFirstTask() || !go.runSecondTask()) return 0;

    return 0;
}
