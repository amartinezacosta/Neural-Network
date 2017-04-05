#include "Network.h"

Network::Network(){
	_InputVectorSize = 0;
	_OutputVectorSize = 0;
}

Network::~Network(){

}

int Network::LoadIOFile(char *file){
	std::ifstream IOfile(file);
	std::string line;
	std::stringstream ss;
	float vector_entry;
	
	if(!IOfile){
		return -1;
	}
	
	std::getline(IOfile, line);
	ss.clear();
	ss.str("");
	ss << line;
	ss >> _InputVectorSize;
	ss >> _OutputVectorSize;
	
	std::cout << _InputVectorSize << std::endl;
	std::cout << _OutputVectorSize << std::endl;
	
	while(std::getline(IOfile, line)){
		ss.clear();
		ss.str("");
		ss << line;
		
		while(ss >> vector_entry){
			IOVector.push_back(vector_entry);
		}
	}
	
	return 1;
}

int Network::LoadWeightsFile(char *file){
	std::ifstream IOfile(file);
	std::string line;
	std::stringstream ss;
	float vector_entry;
	
	if(!IOfile){
		return -1;
	}
	
	while(std::getline(IOfile, line)){
		ss.clear();
		ss.str("");
		ss << line;
		
		while(ss >> vector_entry){
			Weights.push_back(vector_entry);
			std::cout << std::fixed << vector_entry << std::endl; 
		}			
	}
	
	return 1;
}