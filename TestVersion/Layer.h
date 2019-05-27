#pragma once
//#ifndef LAYER_H
//#define LAYER_H
#include "Perceptron.h"
#include <vector>



using namespace std;
class Layer
{
public:
	Layer(int countPerceptrons, Layer* privLayer,float h);
	Layer(int countPerceptrons, Layer* privLayer, float h, float*w);
	~Layer();

	Perceptron *getPerceptron(int number);
	vector<Perceptron *> getPerceptronsInLayer();
	void setPerceptronValuesForLayer(float* inputTrain);
	void calculateSetPerceptronValueForLayer();
	void calculatePerceptronDeltaForLayer();
	int getCountPerceptrons();

	Layer* getPriviousLayer();

	void showNumberPerceptron();	
	void calculatePerceptronWeightForLayer();
	void testPerceptron(float* inputTest);

private:
	float h;
	int count;
	vector<Perceptron*> percList;
	int countPrivPerceptrons;
	Layer* priviousLayer;

};
//}
//#endif
