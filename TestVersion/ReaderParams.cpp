#include "stdafx.h"
#include "ReaderParams.h"

//using namespace std;
ReaderParams::ReaderParams()
{
}

static bool defendParam;
static int params;

ReaderParams::~ReaderParams()
{
}
float s2f(string str)
{
	istringstream buffer(str);
	float temp;
	buffer >> temp;
	return temp;
}
vector<InputTrainParams*> ReaderParams::getParamsInputOutput(string path, int countInput, int countOutput)
{
	defendParam = false;
	string lines,l;
	ifstream myfile(path);
	vector<InputTrainParams*> inputOutputList;
	char delim = ' ';			
	int i = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, lines))
		{
			stringstream ss(lines);
			float *fInput=new float[countInput];
			float *fOutput =new float[countOutput];
			
			i = 0;
			while (getline(ss, l, delim))
			{
				try {
					//if first line isn't string or d or init
					if (isdigit(l.c_str()[0])|| l.c_str()[0]=='-'||defendParam) {
						float temp = s2f(l);						
						if (i <= (countInput+ countOutput)) {
							if (i<countInput) {
								fInput[i] = temp;
							}
							else {								
								fOutput[i - countInput] = temp;
							}							
						}						
						i++;
					}
					else {
							params++;
					}
				}
				catch (exception) {
						params++;
				}
			}
			
			if (params > 0&&defendParam) {
				InputTrainParams *train = new InputTrainParams(fInput, fOutput, countInput, countOutput);
				inputOutputList.push_back(train);
			}
			defendParam = true;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	return inputOutputList;
}