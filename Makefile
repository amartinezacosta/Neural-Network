CC = g++
C_FLAGS = -g -Wall
SRC_PATH = src/
BIN_PATH = bin/
TARGET = NeuralNetwork

all:$(TARGET)

$(TARGET): Network.o $(TARGET).o
	$(CC) -o $(TARGET) $(BIN_PATH)$(TARGET).o $(BIN_PATH)Network.o $(BIN_PATH)Neuron.o
	
$(TARGET).o: $(SRC_PATH)$(TARGET).cpp
	$(CC) -c $(SRC_PATH)$(TARGET).cpp -o $(BIN_PATH)$(TARGET).o
	
Network.o: Neuron.o $(SRC_PATH)Network.cpp $(SRC_PATH)Network.h
	$(CC) -c $(SRC_PATH)Network.cpp -o $(BIN_PATH)Network.o
		
Neuron.o: $(SRC_PATH)Neuron.cpp $(SRC_PATH)Neuron.h
	$(CC) -c $(SRC_PATH)Neuron.cpp -o $(BIN_PATH)Neuron.o
	
clean:
	rm $(BIN_PATH)*.o
	rm *.exe