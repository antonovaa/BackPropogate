// TestVersion.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <math.h>
#include "MultiOutNeuronNetwork.h"
#include "Layer.h"
#include "ReaderParams.h"

using namespace std;

int main(int argc, const char * argv[]) {

	setlocale(LC_ALL, "Rus");

	//count layers and hidden perceptrons =
	int a[] = { 3,2 };

	//int *b;
	//b = a;
	//cout << b<<"   "<<a<<"   "<<b[0]<<endl;

	//ReaderParams *rp = new ReaderParams();
	vector<InputTrainParams*> input = ReaderParams::getParamsInputOutput("C:\\NNBP\\BackPropogate\\train.txt", 3, 1);
	vector<InputTrainParams*> inputTest = ReaderParams::getParamsInputOutput("C:\\NNBP\\BackPropogate\\test.txt", 3, 1);

	int lenght = sizeof(a) / sizeof(*a);
	MultiOutNeuronNetwork* multiOutNeuronNetwork = new MultiOutNeuronNetwork(1, 3, lenght, a, input,0.1);
	multiOutNeuronNetwork->showNumberPerceptron();
	//multiOutNeuronNetwork->testPerceptron(inputTest);

	for (int  k = 0; k < 122330; k++)
	{
			multiOutNeuronNetwork->startTrain();
	}

	multiOutNeuronNetwork->testPerceptron(inputTest);

	multiOutNeuronNetwork->showNumberPerceptron();
	//multiOutNeuronNetwork->startTrain();

	//list<float*>::iterator it = input.begin();

	//input[0]->showTrainInputOutput();
	//input[2]->showTrainInputOutput();

	// Максимальное количество повторений обучения
	long num_iter = 2000000;
	// Минимальная допустимая средняя квадротичная ошибка
	double Thresh = 0.00001;

	long i;
	for (i = 0; i < num_iter; i++) {


	}



	return 0;
}