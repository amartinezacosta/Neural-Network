#include "Neuron.h"

Neuron::Neuron(){
}

Neuron::~Neuron(){
}

void Neuron::SetWeights(std::vector<float> weights){
	_Weights = weights;
}

void Neuron::PrintNeuronWeights(void){
	for(int i = 0; i < _Weights.size(); i++){
		std::cout << _Weights[i] << std::endl;
	}
	
	std::cout << "\n\n";
}

void Neuron::AddWeigthedInputs(std::vector<float> inputs){
	/*Iterate over every input vector element and mutiply by the weights. 
	Check if weights vector size is equal to input vector size, 
	if not then a bias is being used for this neuron which means that we 
	should place a value 1 to element 0 of the vector*/
	if(inputs.size() != _Weights.size()){
		inputs.insert(inputs.begin(), 1);
	}
	
	for(int i = 0; i < inputs.size(); i++){
		_SumWInputs += inputs[i] * _Weights[i];
	}
}

float Neuron::ApplyActivationFunction(void){
	/*Apply sigmoid function using the sum of weigthed inputs*/
	_Output = 1 / (1 + exp(-_SumWInputs));
	return _Output;
}
