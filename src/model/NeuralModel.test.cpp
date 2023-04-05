#include "NeuralModel.hpp"
#include "GeneticModel.test.hpp"

using namespace GeneticModels;

class NeuralModelTests : public GeneticModelTests
{
public:
	std::unique_ptr<GeneticModel> createModel()
	{
		return std::unique_ptr<GeneticModel>(new NeuralModel({ 3 }));
	}

	//TODO Add evaluation test
};

TEST_CASE("LinearGeneticModel", "[LinearGeneticModel]")
{
	NeuralModelTests testClass;

	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
}