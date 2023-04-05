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

	ModelPtr getTestModel() override
	{
		return std::make_unique<NeuralModel>(NeuralModel({ 3, 3 }));
	}

	ModelPtr getBlankModel() override
	{
		return std::make_unique<NeuralModel>(NeuralModel());
	}

	//TODO Add evaluation test
};

TEST_CASE("NeuralModel", "[NeuralModel]")
{
	NeuralModelTests testClass;

	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
}