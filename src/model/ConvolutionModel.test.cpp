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

	ModelPtr getTestModel() override
	{
		return std::make_unique<ConvolutionModel>(ConvolutionModel());
	}

	ModelPtr getBlankModel() override
	{
		return std::make_unique<ConvolutionModel>(ConvolutionModel());
	}

	//TODO Add evaluation test
};

TEST_CASE("ConvolutionModel", "[ConvolutionModel]")
{
	ConvolutionModelTests testClass;

	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
}