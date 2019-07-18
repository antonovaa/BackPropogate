#pragma once
#include "InputTrainParams.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <vector>

using namespace std;
class ReaderParams
{
public:
	ReaderParams();
	~ReaderParams();
	static vector<InputTrainParams*> getParamsInputOutput(string path, int countInput, int countOutput);
};

