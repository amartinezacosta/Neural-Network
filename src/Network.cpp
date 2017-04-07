#include "Network.h"

Network::Network(){
	_InputVectorSize = 0;
	_OutputVectorSize = 0;
	_TrainingSamplesCount = 0;
	_TargetsCount = 0;
	_NeuronCount = 0;
	_HiddenNeuronCount = 0;
}

Network::~Network(){

}

float Network::FeedForward(int sample_index){
	/*iterate over every neuron in the hidden layer compute the sum of weighted inputs
	and apply the activation function*/
	float output;
	std::vector<float> hlayer_outputs;
	
	for(int i = 0; i < _HiddenNeuronCount; i++){
		HiddenLayer[i].AddWeigthedInputs(InputVectors[sample_index]);
		output = HiddenLayer[i].ApplyActivationFunction();
		hlayer_outputs.push_back(output);
	}
	
	/*rest of the neurons should be at the output layer*/
	for(int i = _HiddenNeuronCount; i < _NeuronCount; i++){
		HiddenLayer[i].AddWeigthedInputs(hlayer_outputs);
		output = HiddenLayer[i].ApplyActivationFunction();
	}
	
	/*This should be a vector*/
	return output;
}

int Network::GetTrainingSamplesCount(void){
	return _TrainingSamplesCount;
}

void Network::PrintNetworkInfo(void){
	std::cout << "Input Vector Size: " << _InputVectorSize << std::endl;
	std::cout << "Ouput Vector Size: " << _OutputVectorSize << std::endl;
	std::cout << "Trainig Sample Count: " << _TrainingSamplesCount << std::endl;
	std::cout << "Targets Count: " << _TargetsCount << std::endl;
	std::cout << "Neuron Count: " << _NeuronCount << std::endl;
	std::cout << "\n\n";
	
}

void Network::PrintWeights(void){
	std::cout << "Weights" << std::endl;
	for(int i = 0; i < Weights.size(); i++){
		std::cout << std::fixed << Weights[i] << std::endl; 
	}
	
	std::cout << "\n\n";
}

void Network::PrintInputVectors(void){
	for(int i = 0; i < _TrainingSamplesCount; i++){
		std::cout << "Input Vector " << i << std::endl;
		for(int j = 0; j < _InputVectorSize; j++){
			std::cout << std::fixed << InputVectors[i][j] << std::endl;
		}
	}
	
	std::cout << "\n\n";
}

void Network::PrintOutputVectors(void){
	for(int i = 0; i < _TargetsCount; i++){
		std::cout << "Output Vector " << i << std::endl;
		for(int j = 0; j < _OutputVectorSize; j++){
			std::cout << std::fixed << OutputVectors[i][j] << std::endl;
		}
	}
	
	std::cout << "\n\n";
}

int Network::LoadIOFile(char *file){
	std::ifstream IOfile(file);
	std::string line;
	std::stringstream ss;
	float vector_entry;
	std::vector<float> IOVector;
	
	if(!IOfile){
		return 0;
	}
	
	/*First line of the file defines size of input and output vectors*/
	std::getline(IOfile, line);
	ss.clear();
	ss.str("");
	ss << line;
	ss >> _InputVectorSize;
	ss >> _OutputVectorSize;
		
	/*Separate input vector values and output vector values, rest of the file.
	Each new line means we have a new training sample and target output*/
	while(std::getline(IOfile, line)){
		ss.clear();
		ss.str("");
		ss << line;
		
		/*Resize Input and Output Vectors*/
		_TrainingSamplesCount++;
		_TargetsCount++;
		InputVectors.resize(_TrainingSamplesCount);
		OutputVectors.resize(_TargetsCount);
		
		/*Sort values into their corresponding vectors*/
		for(int i = 0; i < _InputVectorSize; i++){
			ss >> vector_entry;
			InputVectors[_TrainingSamplesCount - 1].resize(i);
			InputVectors[_TrainingSamplesCount - 1].push_back(vector_entry);
		}
		
		for(int i = 0; i < _OutputVectorSize; i++){
			ss >> vector_entry;
			OutputVectors[_TrainingSamplesCount - 1].resize(i);
			OutputVectors[_TrainingSamplesCount - 1].push_back(vector_entry);
		}
	}
	
	
	return 1;
}

int Network::LoadWeightsFile(char *file){
	std::ifstream IOfile(file);
	std::string line;
	std::stringstream ss;
	float vector_entry;
	std::vector<float> neuron_weights;
	
	if(!IOfile){
		return 0;
	}
	
	/*Every new line read means we have a new neuron*/
	while(std::getline(IOfile, line)){
		ss.clear();
		ss.str("");
		ss << line;
		
		while(ss >> vector_entry){
			Weights.push_back(vector_entry);
			neuron_weights.push_back(vector_entry);
		}
		
		/*Resize hidden layer neuron vector and reset neuron weights vector size*/
		_NeuronCount++;
		HiddenLayer.resize(_NeuronCount);
		HiddenLayer[_NeuronCount - 1].SetWeights(neuron_weights);
		neuron_weights.resize(0);
	}
	
	/*Hidden Neurons is equal to the neuron count minus the ouput vector size 
	(how many outputs we have at the last layer)*/
	_HiddenNeuronCount = _NeuronCount - _OutputVectorSize;
	
	return 1;
}