all:NeuralNetwork

NeuralNetwork: Network.o NeuralNetwork.o
	g++ -o NeuralNetwork NeuralNetwork.o Network.o Layer.o
	
NeuralNetwork.o: NeuralNetwork.cpp
	g++ -c NeuralNetwork.cpp
	
Network.o: Layer.o Network.cpp Network.h
	g++ -c Network.cpp
	
Layer.o: Layer.cpp Layer.h
	g++ -c Layer.cpp