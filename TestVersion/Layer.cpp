#include "stdafx.h"
#include "Layer.h"

Layer::Layer(int countPerceptrons,Layer* privLayer,float h):priviousLayer(privLayer), count(countPerceptrons),h(h)
{
	if (priviousLayer) {
		countPrivPerceptrons = priviousLayer->getCountPerceptrons();
		for (int i = 0; i < getCountPerceptrons(); i++)
		{
			Perceptron *p = new Perceptron(priviousLayer->getPerceptronsInLayer());
			percList.push_back(p);
		}
	}
	else {
		countPrivPerceptrons = 0;
		for (int i = 0; i < getCountPerceptrons(); i++)
		{
			vector<Perceptron*> a;
			Perceptron *p = new Perceptron(a);
			percList.push_back(p);
		}
		
	}

}
Layer::Layer(int countPerceptrons, Layer* privLayer, float h, float*w) :Layer(countPerceptrons, privLayer, h)
{
	if (priviousLayer) {
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < countPrivPerceptrons; j++)
			{
				float w3 = w[(j*countPrivPerceptrons) +i ];
				getPerceptron(i)->setWeight(i,w3);

			}
		}

	}
}
Layer::~Layer()
{
}

Perceptron * Layer::getPerceptron(int number)
{
	return percList[number];
}

vector<Perceptron*> Layer::getPerceptronsInLayer()
{
	return percList;
}

void Layer::setPerceptronValuesForLayer(float* inputTrain)
{
	for (int i = 0; i < getCountPerceptrons(); i++)
	{
		percList[i]->setFactValue(inputTrain[i]);
	}
}
//void Layer::setPerceptronWeightForLayer()
//{
//	for (int i = 0; i < count; i++)
//	{
//		percList[i]->setWeight(0.0f);
//	}
//}
void Layer::calculateSetPerceptronValueForLayer()
{
	float tempValue = 0;
	float value, weight;
	for (int j = 0; j < getCountPerceptrons(); j++) {
		tempValue = 0;
		for (int i = 0; i < getPriviousLayer()->getCountPerceptrons(); i++)
		{
			value= getPriviousLayer()->getPerceptron(i)->getValue();
			weight = getPerceptron(j)->getWeight()[i];
			tempValue += value * weight;
		}
		percList[j]->setValue(tempValue);
	}
}

void Layer::calculatePerceptronDeltaForLayer()
{
	for (int i = 0; i < countPrivPerceptrons; i++)
	{
		float tempDelta = 0;
		for (int j = 0; j < getCountPerceptrons(); j++)
		{
			float weightPrivPerc = getPerceptron(j)->getWeight()[i];
			float deltaCurrentPerc = getPerceptron(j)->getDeltaError();
			tempDelta += weightPrivPerc * deltaCurrentPerc;
		}
		float value = getPriviousLayer()->getPerceptron(i)->getValue();
		getPriviousLayer()->getPerceptron(i)->setDeltaError(tempDelta*value*(1- value));
	}
}

int Layer::getCountPerceptrons() {
	return count;
}

Layer * Layer::getPriviousLayer()
{
	return priviousLayer;
}

void Layer::showNumberPerceptron()
{
	for (int i = 0; i < getCountPerceptrons(); i++)
	{
		cout << "Value  Perceptron[" << i << "]=" << percList[i]->getValue()<< endl;
		percList[i]->showWeightPerceptron();
	}
}

void Layer::calculatePerceptronWeightForLayer()
{
	for (int i = 0; i < getCountPerceptrons(); i++)
	{
		for (int j = 0; j < countPrivPerceptrons; j++)
		{
			float weightPrivPerc = getPerceptron(i)->getWeight()[j];
			float deltaCurrentPerc = getPerceptron(i)->getDeltaError();
			float value = getPriviousLayer()->getPerceptron(j)->getValue();
			getPerceptron(i)->setWeight(j, weightPrivPerc+ deltaCurrentPerc* value*h);
		}
	}
}

void Layer::testPerceptron(float * inputTest)
{

	//for()

}
