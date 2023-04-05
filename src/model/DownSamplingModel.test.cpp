#include "DownSamplingModel.hpp"
#include "GeneticModel.test.hpp"

using namespace GeneticModels;

class DownSamplingModelTests : public GeneticModelTests
{
public:
	std::unique_ptr<GeneticModel> createModel()
	{
		return std::unique_ptr<GeneticModel>(new DownSamplingModel(3, 3, 100, 100));
	}

	ModelPtr getTestModel() override
	{
		return std::make_unique<DownSamplingModel>(DownSamplingModel(3, 3, 100, 100));
	}

	ModelPtr getBlankModel() override
	{
		return std::make_unique<DownSamplingModel>(DownSamplingModel());
	}

	//TODO Add evaluation test
};

TEST_CASE("DownSamplingModel", "[DownSamplingModel]")
{
	DownSamplingModelTests testClass;

	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
}