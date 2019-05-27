#pragma once
#include "InputTrainParams.h"
#include <vector>

class Perceptron
{
public:
	
	Perceptron(vector<Perceptron*> PrivPerceptron);
	
	~Perceptron();
	void setFactValue(float newValue);
	// Сигмоид функция
	float sigmoid(float in);
	float *getWeight() {return weight;}
	void setWeight(float *newWeight) {weight = newWeight;}
	void setWeight(int n,float w) {
		weight[n]=w;
	}
	float getDeltaError() {
		return deltaError;
	}
	void setDeltaError(float newDeltaError) {
		deltaError = newDeltaError;
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
	float deltaError;
	float value;
	vector<Perceptron*> PrivPerceptron;
};