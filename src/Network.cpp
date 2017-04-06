#include "Network.h"

Network::Network(){
	_InputVectorSize = 0;
	_OutputVectorSize = 0;
	_TrainingSamplesCount = 0;
	_TargetsCount = 0;
	_NeuronCount = 0;
}

Network::~Network(){

}

void Network::FeedForward(void){
	/*iterate over every neuron in the hidden layer computer the sum of weighted inputs
	and apply the activation function*/
	
	for(int i = 0; i < NeuronCount; i++){
	}
	
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
	int vector_no = 1;
	int i = 0;
	
	while(i < InputVectors.size()){
		std::cout << "Input Vector " << vector_no << std::endl;
		for(int j = 0; j < _InputVectorSize; j++){
			std::cout << InputVectors[i++] << std::endl;
		}
		vector_no++;
	}
	
	std::cout << "\n\n";
}

void Network::PrintOutputVectors(void){
	int vector_no = 1;
	int i = 0;
	
	while(i < OutputVectors.size()){
		std::cout << "Output Vector " << vector_no << std::endl;
		for(int j = 0; j < _OutputVectorSize; j++){
			std::cout << OutputVectors[i++] << std::endl;
		}
		vector_no++;
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
		
	/*Separate input vector values and output vector values, rest of the file*/
	while(std::getline(IOfile, line)){
		ss.clear();
		ss.str("");
		ss << line;
		
		for(int i = 0; i < _InputVectorSize; i++){
			ss >> vector_entry;
			InputVectors.push_back(vector_entry);
		}
		
		for(int i = 0; i < _OutputVectorSize; i++){
			ss >> vector_entry;
			OutputVectors.push_back(vector_entry);
		}
	}
	
	_TrainingSamplesCount = InputVectors.size() / _InputVectorSize;
	_TargetsCount = OutputVectors.size() / _OutputVectorSize;
	
	return 1;
}

int Network::LoadWeightsFile(char *file){
	std::ifstream IOfile(file);
	std::string line;
	std::stringstream ss;
	float vector_entry;
	
	if(!IOfile){
		return 0;
	}
	
	/*Every new line read means we have a neuron in a hidden layer*/
	while(std::getline(IOfile, line)){
		ss.clear();
		ss.str("");
		ss << line;
		
		while(ss >> vector_entry){
			Weights.push_back(vector_entry);
		}
		_NeuronCount++;
	}
	/*Resize hidden layer neuron vector*/
	HiddenLayer.resize(_NeuronCount);
	
	return 1;
}