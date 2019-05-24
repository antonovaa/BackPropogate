#include "stdafx.h"
#include "Layer.h"

Layer::Layer(int countPerceptrons,Layer* privLayer):priviousLayer(privLayer), count(countPerceptrons)
{

}
void Layer::createLayer() {
	if (priviousLayer) {
		countPrivPerceptrons = priviousLayer->getCountPerceptrons();
	}
	else {
		countPrivPerceptrons = 0;
	}

	for (int i = 0; i < count; i++)
	{
		Perceptron *p = new Perceptron(priviousLayer);
		percList.push_back(p);
	}
}

Layer::~Layer()
{
}

Perceptron * Layer::getPerceptron(int number)
{
	return percList[number];
}

void Layer::setPerceptronValuesForLayer(float* inputTrain)
{
	for (int i = 0; i < count; i++)
	{
		percList[i]->setValue(inputTrain[i]);
	}
}
//void Layer::setPerceptronWeightForLayer()
//{
//	for (int i = 0; i < count; i++)
//	{
//		percList[i]->setWeight(0.0f);
//	}
//}
void Layer::calculateSetPerceptronValueForLayer(Layer* prevLayer)
{
	float tempValue = 0;
	for (int j = 0; j < getCountPerceptrons(); j++) {
		tempValue = 0;
		for (int i = 0; i < prevLayer->getCountPerceptrons(); i++)
		{
			tempValue += prevLayer->getPerceptron(i)->getValue();
		}
		percList[j]->setValue(tempValue);
	}
}

int Layer::getCountPerceptrons() {
	return count;
}

void Layer::showNumberPerceptron()
{
	for (int i = 0; i < getCountPerceptrons(); i++)
	{
		cout << "Perceptron[" << i << "]=" << endl << endl;
		percList[i]->showWeightPerceptron();
	}
}
