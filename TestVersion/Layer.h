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


	void createLayer();
	Perceptron *getPerceptron(int number);
	void setPerceptronValuesForLayer(float* inputTrain);
	//void setPerceptronWeightForLayer();
	void calculateSetPerceptronValueForLayer(Layer* prevLayer);
	int getCountPerceptrons();

	void showNumberPerceptron();
private:
	int count;
	vector<Perceptron*> percList;
	int countPrivPerceptrons;
	Layer* priviousLayer;

};
//}
//#endif
