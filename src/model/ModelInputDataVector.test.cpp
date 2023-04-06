#include "ModelInputData.test.hpp"

#include "ModelInputDataVector.hpp"

class ModelInputDataVectorTests : public ModelInputDataTests
{
public:
	DataPtr getTestData() override { return std::make_unique<GeneticModels::ModelInputDataVector>(GeneticModels::ModelInputDataVector({ 1, 2, 3, 4, 5 })); }
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
