#pragma once
#include "InputTrainParams.h"
#include <vector>

class Perceptron
{
public:
	
	Perceptron(vector<Perceptron*> PrivPerceptron);
	
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
private:
	int countPerceptronsInPrivLayer;
	float *weight;
	float oldWeight;
	float delta;
	float value;
	vector<Perceptron*> PrivPerceptron;
};