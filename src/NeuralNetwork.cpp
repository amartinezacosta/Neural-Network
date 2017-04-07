#include "Network.h"

int main(int argc, char **argv){
	Network ANN;
	
	if(argc < 3){
		std::cout << "usage: [I/O Vector File] [Weights File]" << std::endl;
		return -1;
	}
	
	if(!ANN.LoadIOFile(argv[1])){
		std::cout << "Failed to load input ouput vector file " << argv[1] << std::endl;
		return -1;
	}
	
	if(!ANN.LoadWeightsFile(argv[2])){
		std::cout << "Failed to load input weights file " << argv[2] << std::endl;
		return -1;
	}
	
	ANN.PrintNetworkInfo();
	ANN.PrintInputVectors();
	ANN.PrintOutputVectors();
	ANN.PrintWeights();
	
	for (int i = 0; i < ANN.GetTrainingSamplesCount(); i++){
		std::cout << "FeedForward Output " << i + 1 << ": ";
		std::cout << ANN.FeedForward(i) << std::endl;
	}
		
	return 1;
}