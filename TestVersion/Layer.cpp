#include "stdafx.h"
#include "Layer.h"

Layer::Layer(int countPerceptrons,Layer* privLayer):priviousLayer(privLayer), count(countPerceptrons)
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
void Layer::calculateSetPerceptronValueForLayer()
{
	float tempValue = 0;
	for (int j = 0; j < getCountPerceptrons(); j++) {
		tempValue = 0;
		for (int i = 0; i < getPriviousLayer()->getCountPerceptrons(); i++)
		{
			tempValue += getPriviousLayer()->getPerceptron(i)->getValue();
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
			float deltaCurrentPerc = getPerceptron(j)->getDelta();
			tempDelta += weightPrivPerc * deltaCurrentPerc;
		}
		getPriviousLayer()->getPerceptron(i)->setDelta(tempDelta);

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
