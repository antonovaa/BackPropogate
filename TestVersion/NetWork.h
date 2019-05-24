#pragma once

#include "Layer.h"
#include <vector>

class NetWork
{
public:
	NetWork(int countHiddenLayers,int *hiddenLayers, int countInputParam, vector<InputTrainParams*> inputTrain,int numberOutputParam);
	~NetWork();

	void feedForward();
	void backPropogation();

	void showNumberLayer();

private:
	vector<InputTrainParams*> inputForTrain;
	vector<Layer*> layerList;
	int numberOutputParam;
	int *hiddenLayers;
	int countInputParam;
	int countHiddenLayers;


};

