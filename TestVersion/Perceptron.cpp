#include "stdafx.h"
#include "Perceptron.h"

Perceptron::Perceptron(Layer* prLayer):privLayer(prLayer)
{
	countPerceptronsInPrivLayer = prLayer->getCountPerceptrons();
	weight = new float[countPerceptronsInPrivLayer];
	//init weight random value
	for (int i = 0; i < countPerceptronsInPrivLayer; i++)
	{
		weight[i] = (float)(rand()) / (RAND_MAX / 2) - 1;

		oldWeight = 0.0f;
	}	
}
//void Perceptron::startTest() {
//	countPerceptronsInPrivLayer = getPrivLayer()->getCountPerceptrons();
//	weight = new float[countPerceptronsInPrivLayer];
//	//init weight random value
//	for (int i = 0; i < countPerceptronsInPrivLayer; i++)
//	{
//		weight[i] = (float)(rand()) / (RAND_MAX / 2) - 1;
//
//		oldWeight = 0.0f;
//	}
//}



void Perceptron::setWeightLinkPrivLayer(int countPerceptronsInPrivLayer) {
	countPerceptronsInPrivLayer = countPerceptronsInPrivLayer;
	weight = new float[countPerceptronsInPrivLayer];
	//init weight random value
	for (int i = 0; i < countPerceptronsInPrivLayer; i++)
	{
		weight[i] = (float)(rand()) / (RAND_MAX / 2) - 1;
		
		oldWeight = 0.0f;
	}
}

void Perceptron::showWeightPerceptron() {
	for (int i = 0; i < countPerceptronsInPrivLayer; i++)
	{
		cout << "weight[" << i << "]=" << weight[i] << endl;
	}
	
}


Perceptron::~Perceptron()
{
}

void Perceptron::setValue(float newValue)
{
	value = sigmoid(newValue);
}

float Perceptron::sigmoid(float in)
{
	return (float)(1 / (1 + exp(-in)));
}
