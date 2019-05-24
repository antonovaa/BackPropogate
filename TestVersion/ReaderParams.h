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

	/*
	path=path to file;
	file must suit that:	a s d ff gg 
								1 3 44 21 1 
								32 3 2 2 5
								..........	
	for get all params 
	*/
	//vector<InputTrainParams*> getParamsInputOutput(string path, int& countParam, int countInput,int countOutput);
	static vector<InputTrainParams*> getParamsInputOutput(string path, int countInput, int countOutput);
	//vector<InputTrainParams*> getParamsInputOutput(string path, int& countParam, int countInput, int params);
private:

	//bool withParams=false;
};

