#include "stdafx.h"
#include "NetWork.h"

//using namespace LNN;

NetWork::NetWork(int countHiddenLayers, int *hiddenLayers, int countInputParam, vector<InputTrainParams*> inputTrain,int numberOutputParam) : hiddenLayers(hiddenLayers), countInputParam(countInputParam), inputForTrain(inputTrain), numberOutputParam(numberOutputParam), countHiddenLayers(countHiddenLayers){

	//create layer for input params
	Layer *lStart = new Layer(countInputParam,nullptr);
	layerList.push_back(lStart);

	//todo Init; start init memory
	for (int i = 0; i < countHiddenLayers; i++)
	{
		Layer *l = new Layer(hiddenLayers[i], layerList[i]);
		layerList.push_back(l);
	}
	Layer *lEnd = new Layer(1, layerList[countHiddenLayers]);
	layerList.push_back(lEnd);

}

NetWork::~NetWork()
{
}

void NetWork::feedForward()
{
	//количество итераций набора входных данных для обучения
	int trainData = (int)inputForTrain.size();
	for (int i = 0; i < trainData; i++)
	{
		//Инициализация данных для входного слоя нейронов
		layerList[0]->setPerceptronValuesForLayer(inputForTrain[i]->getInput());
		//расчет начинаем с первого слоя! не нулевого!
		for (int j = 1; j <= countHiddenLayers+1; j++)
		{
			layerList[j]->calculateSetPerceptronValueForLayer();
		}
		float targetOutData = inputForTrain[i]->getOutput()[numberOutputParam];
		float factOutData = layerList[countHiddenLayers+1]->getPerceptron(0)->getValue();
		float delta = targetOutData - factOutData;
		layerList[countHiddenLayers+1]->getPerceptron(0)->setDelta(delta);
		cout <<"  Value =  "<< layerList[countHiddenLayers]->getPerceptron(0)->getValue()<<endl;

		backPropogation();

	}
}

void NetWork::backPropogation()
{
	//start find delta

	for (int i = countHiddenLayers+1; i >=1 ; i--)
	{
		layerList[i]->calculatePerceptronDeltaForLayer();
	}

}

void NetWork::showNumberLayer()
{
	for (int i = 0; i <= countHiddenLayers+1; i++)
	{
		cout << endl << "Layer[" << i << "]=" << endl;
		layerList[i]->showNumberPerceptron();
	}
}
