#include "stdafx.h"
#include "NetWork.h"

//using namespace LNN;

NetWork::NetWork(int countHiddenLayers, int *hiddenLayers, int countInputParam, vector<InputTrainParams*> inputTrain,int numberOutputParam,float h) : 
	hiddenLayers(hiddenLayers), 
	countInputParam(countInputParam),
	inputForTrain(inputTrain),
	numberOutputParam(numberOutputParam),
	countHiddenLayers(countHiddenLayers),
	h(h){

	//create layer for input params
	Layer *lStart = new Layer(countInputParam,nullptr,h);
	layerList.push_back(lStart);

	//for test
	float w[] = { -1,2,1,1,3,-2 };
	//todo Init; start init memory
	for (int i = 0; i < countHiddenLayers; i++)
	{
		Layer *l = new Layer(hiddenLayers[i], layerList[i], h,w);
		layerList.push_back(l);
	}
	float w2[] = { 1,2,4 };
	Layer *lEnd = new Layer(1, layerList[countHiddenLayers], h,w2);
	layerList.push_back(lEnd);

}

NetWork::~NetWork()
{
}

void NetWork::feedForward()
{
	//количество итераций набора входных данных дл€ обучени€
	int trainData = (int)inputForTrain.size();
	for (int i = 0; i < trainData; i++)
	{
		//»нициализаци€ данных дл€ входного сло€ нейронов
		layerList[0]->setPerceptronValuesForLayer(inputForTrain[i]->getInput());
		//расчет начинаем с первого сло€! не нулевого!
		for (int j = 1; j <= countHiddenLayers+1; j++)
		{
			layerList[j]->calculateSetPerceptronValueForLayer();
		}
		float targetOutData = inputForTrain[i]->getOutput()[numberOutputParam];
		float factOutData = layerList[countHiddenLayers+1]->getPerceptron(0)->getValue();
		float delta = (targetOutData - factOutData)*factOutData*(1- factOutData);
		layerList[countHiddenLayers+1]->getPerceptron(0)->setDeltaError(delta);
		cout <<"  targetOutData =  "<< targetOutData<<"  factOutData =  "<< factOutData<<endl;

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
	//correct weight for each layer
	for (int i = 1 ; i < countHiddenLayers+1; i++)
	{
		layerList[i]->calculatePerceptronWeightForLayer();
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

void NetWork::testLayers(vector<InputTrainParams*> inputTrain)
{
	int testData = (int)inputTrain.size();
	for (int i = 0; i < testData; i++)
	{
		layerList[0]->setPerceptronValuesForLayer(inputTrain[i]->getInput());
		//расчет начинаем с первого сло€! не нулевого!
		for (int j = 1; j <= countHiddenLayers + 1; j++)
		{
			layerList[j]->calculateSetPerceptronValueForLayer();
		}
		float factOutData = layerList[countHiddenLayers + 1]->getPerceptron(0)->getValue();
		cout << endl << " input: ";
		for (int k = 0; k < countInputParam; k++)
		{
			cout << "  param" << k << " = " << inputTrain[i]->getInput()[k];
		}
		cout << "  result=  "<< factOutData<< endl;
		
	}


}