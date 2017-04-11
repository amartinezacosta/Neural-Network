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

std::vector<float> Network::FeedForward(int sample_index){
	/*iterate over every neuron in the hidden layer compute the sum of weighted inputs
	and apply the activation function*/
	float temp_output;
	std::vector<float> hlayer_outputs;
	std::vector<float> outputs;
	
	/*Hidden Layer feedforward and activation for all the neurons*/
	for(int i = 0; i < _HiddenNeuronCount; i++){
		HiddenLayer[i].AddWeigthedInputs(InputVectors[sample_index]);
		temp_output = HiddenLayer[i].ApplyActivationFunction();
		hlayer_outputs.push_back(temp_output);
	}
	
	/*rest of the neurons should be at the output layer*/
	for(int i = 0; i < _OutputVectorSize; i++){
		OutputLayer[i].AddWeigthedInputs(hlayer_outputs);
		temp_output = OutputLayer[i].ApplyActivationFunction();
		outputs.push_back(temp_output);
	}
	
	/*This should be a vector*/
	return outputs;
}

int Network::GetTrainingSamplesCount(void){
	return _TrainingSamplesCount;
}

int Network::GetOutputVectorSize(void){
	return _OutputVectorSize;
}

void Network::PrintNetworkInfo(void){
	std::cout << "Input Vector Size: " << _InputVectorSize << std::endl;
	std::cout << "Ouput Vector Size: " << _OutputVectorSize << std::endl;
	std::cout << "Trainig Sample Count: " << _TrainingSamplesCount << std::endl;
	std::cout << "Targets Count: " << _TargetsCount << std::endl;
	std::cout << "Neuron Count: " << _NeuronCount << std::endl;
	std::cout << "Neuron Count in Hidden Layer: " << _HiddenNeuronCount << std::endl;
	std::cout << "\n\n";
	
}

void Network::PrintWeights(void){
	std::vector< std:: vector<float> >::const_iterator row;
	std::vector<float>::const_iterator col;
	int i = 0;
	
	for(row = Weights.begin(); row != Weights.end(); ++row){
		std::cout << "Weights Set " << i++ << std::endl;
		for(col = row->begin(); col != row->end(); ++col){
			std::cout << *col << std::endl;
		}
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
	std::vector<float> temp_weights;
	
	if(!IOfile){
		return 0;
	}
	
	/*Every new line read means we have a new neuron*/
	while(std::getline(IOfile, line)){
		ss.clear();
		ss.str("");
		ss << line;
		
		while(ss >> vector_entry){
			temp_weights.push_back(vector_entry);
		}
		
		Weights.push_back(temp_weights);
		temp_weights.resize(0);
	}
	
	/*Neuron count is just the size of the weights vector.
	The hidden neuron count is given by the number of neurons
	minus the size of the output vector size*/
	_NeuronCount = Weights.size();
	_HiddenNeuronCount = _NeuronCount - _OutputVectorSize;
	
	/*Set size of hiden layer and output layer*/
	HiddenLayer.resize(_HiddenNeuronCount);
	OutputLayer.resize(_OutputVectorSize);
	
	/*Set weights for hidden layer neurons and output layer 
	neurons*/
	for(int i = 0; i < _HiddenNeuronCount; i++){
		HiddenLayer[i].SetWeights(Weights[i]);
	}
	
	for(int i = 0; i < _OutputVectorSize; i++){
		OutputLayer[i].SetWeights(Weights[i +_HiddenNeuronCount]);
	}
	
	return 1;
}