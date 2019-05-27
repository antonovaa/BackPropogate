#pragma once

#include "Layer.h"
#include <vector>

class NetWork
{
public:
	NetWork(int countHiddenLayers,int *hiddenLayers, int countInputParam, vector<InputTrainParams*> inputTrain,int numberOutputParam,float h);
	~NetWork();

	void feedForward();
	void backPropogation();
	void testLayers(vector<InputTrainParams*> inputTrain);
	void showNumberLayer();

private:
	float h;
	vector<InputTrainParams*> inputForTrain;
	vector<Layer*> layerList;
	int numberOutputParam;
	int *hiddenLayers;
	int countInputParam;
	int countHiddenLayers;


};

