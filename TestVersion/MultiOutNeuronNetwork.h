#pragma once

#include "NetWork.h"
//#include <vector>

class MultiOutNeuronNetwork
{
public:
	MultiOutNeuronNetwork(int outputCount, int inputCount,int countHiddenLayers,int *hiddenLayers, vector<InputTrainParams*> inputTrain,float h);
	~MultiOutNeuronNetwork();

	void startTrain();
	int getOutputCount();
	void testPerceptron(vector<InputTrainParams*> inputTrain);
	void showNumberPerceptron();

private:
	float h;
	vector<NetWork*> nnList;
	int outputCount;
	int inputCount;
};

