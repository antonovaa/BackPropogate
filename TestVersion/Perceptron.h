#pragma once
//#ifndef PERCEPTRON_H
//#define PERCEPTRON_H
//#include "Layer.h"
class Layer;
#include "InputTrainParams.h"


class Perceptron
{
public:
	
	Perceptron(Layer* prLayer);
	
	~Perceptron();


	// Сигмоид функция
	float sigmoid(float in);
	float *getWeight() {return weight;}
	void setWeight(float *newWeight) {weight = newWeight;}
	float getOldWeight() {
		return oldWeight;
	}
	void setOldWeight(float weight) {
		oldWeight = weight;
	}
	float getDelta() {
		return delta;
	}
	void setDelta(float newDelta) {
		delta = newDelta;
	}
	float getValue() {
		return value;
	}
	void setValue(float newValue);
	//
	
	//void startTest();

	void showWeightPerceptron();
	void setWeightLinkPrivLayer(int countPerceptronsInPrivLayer);
	Layer* getPrivLayer() {
		return privLayer;
	}
private:
	int countPerceptronsInPrivLayer;
	float *weight;
	float oldWeight;
	float delta;
	float value;
	Layer* privLayer;

};

//#endif