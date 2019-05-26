#pragma once
//#ifndef LAYER_H
//#define LAYER_H
#include "Perceptron.h"
#include <vector>



using namespace std;
class Layer
{
public:
	Layer(int countPerceptrons, Layer* privLayer);
	~Layer();

	Perceptron *getPerceptron(int number);
	vector<Perceptron *> getPerceptronsInLayer();
	void setPerceptronValuesForLayer(float* inputTrain);
	void calculateSetPerceptronValueForLayer();
	void calculatePerceptronDeltaForLayer();
	int getCountPerceptrons();

	Layer* getPriviousLayer();

	void showNumberPerceptron();	
	//void setPerceptronWeightForLayer();

private:
	int count;
	vector<Perceptron*> percList;
	int countPrivPerceptrons;
	Layer* priviousLayer;

};
//}
//#endif
