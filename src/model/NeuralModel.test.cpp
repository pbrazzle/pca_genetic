/*#include "GeneticModel.test.hpp"
#include "NeuralModel.hpp"

using namespace GeneticModels;

class NeuralModelTests : public GeneticModelTests
{
	public:
		std::unique_ptr<GeneticModel> createModel()
		{
			return std::unique_ptr<GeneticModel>(new NeuralModel());
		}
		
		//TODO Add evaluation test
};

int main()
{
	NeuralModelTests tests;
	tests.runTests();
	
	return 0;
}*/

#include <catch2/catch_test_macros.hpp>