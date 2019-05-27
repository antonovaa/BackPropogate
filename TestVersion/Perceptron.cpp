#include "stdafx.h"
#include "Perceptron.h"

Perceptron::Perceptron(vector<Perceptron*> PrivPerceptron) :PrivPerceptron(PrivPerceptron)
{
	countPerceptronsInPrivLayer = (int)PrivPerceptron.size();
	if (countPerceptronsInPrivLayer>0) {
		weight = new float[countPerceptronsInPrivLayer];
		//init weight random value
		for (int i = 0; i < countPerceptronsInPrivLayer; i++)
		{
			weight[i] = (float)(rand()) / (RAND_MAX / 2) - 1;
		}
	}
}



void Perceptron::setWeightLinkPrivLayer(int countPerceptronsInPrivLayer) {
	countPerceptronsInPrivLayer = countPerceptronsInPrivLayer;
	weight = new float[countPerceptronsInPrivLayer];
	//init weight random value
	for (int i = 0; i < countPerceptronsInPrivLayer; i++)
	{
		weight[i] = (float)(rand()) / (RAND_MAX / 2) - 1;
		
	}
}

void Perceptron::showWeightPerceptron() {
	for (int i = 0; i < countPerceptronsInPrivLayer; i++)
	{
		cout << "weight[" << i << "]=" << weight[i]  << "\t";
	}
	cout << endl;
	
}


Perceptron::~Perceptron()
{
}

void Perceptron::setValue(float newValue)
{
	value = sigmoid(newValue);
}

void Perceptron::setFactValue(float newValue)
{
	value = newValue;
}

float Perceptron::sigmoid(float in)
{
	return (float)(1 / (1 + exp(-in)));
}
