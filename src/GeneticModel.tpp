using namespace PCAGenetic;

template <typename T, int numParams>	
GeneticModel<T, numParams>::GeneticModel() { }
	
template <typename T, int numParams>
void GeneticModel<T, numParams>::train(GeneticModel::modelFunc fitnessFunc, int generations) { }

template <typename T, int numParams>
T GeneticModel<T, numParams>::calculateFunc(GeneticModel::modelFunc func) { return T(); }