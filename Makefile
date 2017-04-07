CC = cl
TARGET = NeuralNetwork.exe
SRC_PATH = src/
BIN_PATH = bin/
	
all: $(TARGET)

$(TARGET): NeuralNetwork.obj
	$(CC) /o $(TARGET) $(BIN_PATH)Neuron.obj $(BIN_PATH)Network.obj $(BIN_PATH)NeuralNetwork.obj
	
NeuralNetwork.obj: Network.obj Neuron.obj
	$(CC) /EHsc /Fo.\bin\ /c $(SRC_PATH)NeuralNetwork.cpp
	
Network.obj: $(SRC_PATH)Network.cpp $(SRC_PATH)Network.h
	$(CC) /EHsc /Fo.\bin\ /c $(SRC_PATH)Network.cpp 
	
Neuron.obj: $(SRC_PATH)Neuron.cpp $(SRC_PATH)Neuron.h
	$(CC) /EHsc /Fo.\bin\ /c $(SRC_PATH)Neuron.cpp
	
	

