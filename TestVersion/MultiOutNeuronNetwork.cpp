#include "stdafx.h"
#include "MultiOutNeuronNetwork.h"

/*
outputCount = count params outputs
*/
MultiOutNeuronNetwork::MultiOutNeuronNetwork(int outputCount,int inputCount, int countHiddenLayers, int *hiddenLayers, vector<InputTrainParams*> inputTrain,float h):
	outputCount(outputCount), 
	inputCount(inputCount),
	h(h)
{
	for (int i = 0; i < outputCount; i++)
	{
		NetWork *nn = new NetWork(countHiddenLayers,hiddenLayers, inputCount, inputTrain,i, h);
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
	for (int i = 0; i < getOutputCount(); i++)
	{
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Output params= " << i << endl;
		nnList[i]->showNumberLayer();
	}
}
void MultiOutNeuronNetwork::testPerceptron(vector<InputTrainParams*> inputTrain)
{
	for (int i = 0; i < getOutputCount(); i++)
	{
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Output params for test= " << i << endl;
		nnList[i]->testLayers(inputTrain);
	}
}