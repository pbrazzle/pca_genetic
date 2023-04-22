#include "ModelInputData.test.hpp"

#include "ModelInputDataVector.hpp"

class ModelInputDataVectorTests : public ModelInputDataTests
{
public:
	DataPtr getTestData() override
	{
		std::vector<double> testData{1, 2, 3, 4, 5};
		return std::make_unique<GeneticModels::ModelInputDataVector>(GeneticModels::ModelInputDataVector(testData));
	}
	DataPtr getBlankData() override { return std::make_unique<GeneticModels::ModelInputDataVector>(GeneticModels::ModelInputDataVector()); }
};

TEST_CASE("ModelInputDataVector", "[ModelInputDataVector]")
{
	ModelInputDataVectorTests tests;

	SECTION("Interface Tests")
	{
		tests.runTests();
	}
}
