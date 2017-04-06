#include <vector>

class Neuron{
public:
	Neuron();
	~Neuron();
	
	void SetWeigths(std::vector<float> weights);
	void AddWeigthedInputs(std::vector<float> inputs);
	
private:
	std::vector<float> Weights;

};