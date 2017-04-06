#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Neuron.h"

class Network{
public:
	Network();
	~Network();
	
	int LoadIOFile(char *file);
	int LoadWeightsFile(char *file);
	void PrintWeights(void);
	void PrintInputVectors(void);
	void PrintOutputVectors(void);
	void PrintNetworkInfo(void);
	void FeedForward(void);
	
private:
	int _InputVectorSize;
	int _OutputVectorSize;
	int _TrainingSamplesCount;
	int _TargetsCount;
	int _NeuronCount;
	
	std::vector<float> InputVectors;
	std::vector<float> OutputVectors;
	std::vector<float> Weights;
	
	std::vector<Neuron> HiddenLayer;
};