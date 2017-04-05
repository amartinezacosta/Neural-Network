#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Layer.h"

class Network{
public:
	Network();
	~Network();
	
	int LoadIOFile(char *file);
	int LoadWeightsFile(char *file);
	
private:
	int _InputVectorSize;
	int _OutputVectorSize;
	
	std::vector<float> IOVector;
	std::vector<float> Weights;
	
	std::vector<Layer> HiddenLayers;
};