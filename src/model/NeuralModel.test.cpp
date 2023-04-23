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

	SECTION("Evaluation Tests")
	{
		auto testModel = testClass.getTestModel();

		std::vector<double> inVec{ 1, 1, 1 };
		ModelInputDataVector inData(inVec);

		auto result = testModel->evaluate(inData);
		auto result2 = testModel->evaluate(inData);

		for (int i = 0; i < result->getData().size(); i++)
		{
			REQUIRE(result->getData()[i] == result2->getData()[i]);
		}
	}
}