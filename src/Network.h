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
	std::vector<float> FeedForward(int sample_index);
	
	void PrintWeights(void);
	void PrintInputVectors(void);
	void PrintOutputVectors(void);
	void PrintNetworkInfo(void);
	
	int GetTrainingSamplesCount(void);
	int GetOutputVectorSize(void);
	
private:
	int _InputVectorSize;
	int _OutputVectorSize;
	int _TrainingSamplesCount;
	int _TargetsCount;
	int _NeuronCount;
	int _HiddenNeuronCount;
	
	std::vector< std::vector<float> > InputVectors;
	std::vector< std::vector<float> > OutputVectors;
	std::vector< std::vector<float> > Weights;
	
	std::vector<Neuron> HiddenLayer;
	std::vector<Neuron> OutputLayer;
};