#include <iostream>
#include <vector>
#include <cmath>

class Neuron{
public:
	Neuron();
	~Neuron();
	
	void SetWeights(std::vector<float> weights);
	void AddWeigthedInputs(std::vector<float> inputs);
	float ApplyActivationFunction(void);
	
	void PrintNeuronWeights(void);
	
private:
	std::vector<float> _Weights;
	float _SumWInputs;
	float _Output;
};