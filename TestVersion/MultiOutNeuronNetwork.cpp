#include "stdafx.h"
#include "MultiOutNeuronNetwork.h"

/*
outputCount = count params outputs
*/
MultiOutNeuronNetwork::MultiOutNeuronNetwork(int outputCount,int inputCount, int countHiddenLayers, int *hiddenLayers, vector<InputTrainParams*> inputTrain):outputCount(outputCount), inputCount(inputCount)
{
	for (int i = 0; i < outputCount; i++)
	{
		NetWork *nn = new NetWork(countHiddenLayers,hiddenLayers, inputCount, inputTrain,i);
		nnList.push_back(nn);
	}
}


MultiOutNeuronNetwork::~MultiOutNeuronNetwork()
{
}

void MultiOutNeuronNetwork::startTrain()
{
	for (int i = 0; i < getOutputCount(); i++)
	{
		nnList[i]->feedForward();
	}
}

int MultiOutNeuronNetwork::getOutputCount() {
	return outputCount;
}

void MultiOutNeuronNetwork::showNumberPerceptron()
{
	for (int i = 0; i < outputCount; i++)
	{
		nnList[i]->showNumberLayer();
	}
}
