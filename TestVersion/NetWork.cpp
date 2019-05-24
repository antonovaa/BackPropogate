#include "stdafx.h"
#include "NetWork.h"

//using namespace LNN;

NetWork::NetWork(int countHiddenLayers, int *hiddenLayers, int countInputParam, vector<InputTrainParams*> inputTrain,int numberOutputParam) : hiddenLayers(hiddenLayers), countInputParam(countInputParam), inputForTrain(inputTrain), numberOutputParam(numberOutputParam), countHiddenLayers(countHiddenLayers){

	//create layer for input params
	Layer *lStart = new Layer(countInputParam,nullptr);
	lStart->createLayer();
	layerList.push_back(lStart);
	//todo Init; start init memory
	for (int i = 0; i < countHiddenLayers; i++)
	{
		Layer *l = new Layer(hiddenLayers[i], layerList[i]);
		l->createLayer();
		layerList.push_back(l);
	}
	Layer *lEnd = new Layer(1, layerList[countHiddenLayers]);
	lEnd->createLayer();
	layerList.push_back(lEnd);

	/*for (int i = 1; i <= countHiddenLayers+1; i++)
	{
		for (int j = 0; j < layerList[i]->getCountPerceptrons(); j++)
		{
			layerList[i]->getPerceptron(j)->setWeightLinkPrivLayer(layerList[i - 1]->getCountPerceptrons());
		}
	}*/
	

}

NetWork::~NetWork()
{
}

void NetWork::feedForward()
{
	//количество итераций набора входных данных для обучения
	int trainData = inputForTrain.size();
	for (int i = 0; i < trainData; i++)
	{
		//Инициализация данных для входного слоя нейронов
		layerList[0]->setPerceptronValuesForLayer(inputForTrain[i]->getInput());
		//расчет начинаем с первого слоя! не нулевого!
		for (int i = 1; i <= countHiddenLayers; i++)
		{
			layerList[i]->calculateSetPerceptronValueForLayer(layerList[i - 1]);
		}

		cout <<"  Value =  "<< layerList[countHiddenLayers]->getPerceptron(0)->getValue()<<endl;



		backPropogation();


	}
}

void NetWork::backPropogation()
{
}

void NetWork::showNumberLayer()
{
	for (int i = 0; i <= countHiddenLayers+1; i++)
	{
		cout << "Layer[" << i << "]=" << endl << endl;
		layerList[i]->showNumberPerceptron();
	}
}
