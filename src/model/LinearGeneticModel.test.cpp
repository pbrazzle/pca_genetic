#include "LinearGeneticModel.hpp"
#include "GeneticModel.test.hpp"

using namespace GeneticModels;

class LinearModelTests : public GeneticModelTests
{
	public:
		std::unique_ptr<GeneticModel> createModel()
		{
			return std::unique_ptr<GeneticModel>(new LinearGeneticModel(3));
		}

		ModelPtr getTestModel() override
		{
			return std::make_unique<LinearGeneticModel>(LinearGeneticModel(3));
		}

		ModelPtr getBlankModel() override
		{
			return std::make_unique<LinearGeneticModel>(LinearGeneticModel());
		}

		//TODO Add evaluation test
};

TEST_CASE("LinearGeneticModel", "[LinearGeneticModel]")
{
	LinearModelTests testClass;
	
	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
}