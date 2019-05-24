#pragma once

#include "NetWork.h"
//#include <vector>

class MultiOutNeuronNetwork
{
public:
	MultiOutNeuronNetwork(int outputCount, int inputCount,int countHiddenLayers,int *hiddenLayers, vector<InputTrainParams*> inputTrain);
	~MultiOutNeuronNetwork();

	void startTrain();
	int getOutputCount();

	void showNumberPerceptron();

private:
	vector<NetWork*> nnList;
	int outputCount;
	int inputCount;
};

