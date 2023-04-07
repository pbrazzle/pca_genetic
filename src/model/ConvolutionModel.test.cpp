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
		return std::make_unique<ConvolutionModel>(ConvolutionModel(5, 5, 3, 3, std::vector<double>(9, 1.0)));
	}

	ModelPtr getBlankModel() override
	{
		return std::make_unique<ConvolutionModel>(ConvolutionModel());
	}

	void evalTest()
	{
		ModelInputDataVector input(std::vector<double>(25, 1.0));

		ModelPtr model = getTestModel();
		auto output = model->evaluate(input);

		for (auto val : output->getData())
		{
			REQUIRE(val == 9.0);
		}
	}
};

TEST_CASE("ConvolutionModel", "[ConvolutionModel]")
{
	ConvolutionModelTests testClass;

	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
	SECTION("Evaluation Test")
	{
		testClass.evalTest();
	}
}