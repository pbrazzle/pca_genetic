#include "ConvolutionModel.hpp"
#include "GeneticModel.test.hpp"

using namespace GeneticModels;

class ConvolutionModelTests : public GeneticModelTests
{
public:
	std::unique_ptr<GeneticModel> createModel()
	{
		return std::unique_ptr<GeneticModel>(new ConvolutionModel());
	}

	//TODO Add evaluation test
};

TEST_CASE("LinearGeneticModel", "[LinearGeneticModel]")
{
	ConvolutionModelTests testClass;

	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
}