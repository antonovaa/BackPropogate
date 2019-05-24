#pragma once
#include <iostream>
using namespace std;

class InputTrainParams
{
public:
	InputTrainParams(float*,float*, int inCount, int outCount);
	~InputTrainParams();

	void showTrainInputOutput() {

		cout << endl << "input params: " << endl;
		for (int i = 0; i < inCount; i++)
		{
			cout << "\t¹: " << i << " =" << input[i];
		}
		
		cout <<endl<< "output params: " << endl;
		for (int i = 0; i < outCount; i++)
		{
			cout << "\t¹: " << i << " =" << output[i];
		}

	}

	float * getInput() {
		return input;
	}	
	float * getOutput() {
		return output;
	}

private:
	int inCount;
	int outCount;
	float *input;
	float *output;
};

