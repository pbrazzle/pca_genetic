#include "ModelOutputData.test.hpp"

#include "ModelOutputDataVector.hpp"

class ModelOutputDataVectorTests : public ModelOutputDataTests
{
public:
	DataPtr getTestData() override { return std::make_unique<GeneticModels::ModelOutputDataVector>(GeneticModels::ModelOutputDataVector(std::vector<double>{ 1, 2, 3, 4, 5 })); }
	DataPtr getBlankData() override { return std::make_unique<GeneticModels::ModelOutputDataVector>(GeneticModels::ModelOutputDataVector()); }
};

TEST_CASE("ModelOutputDataVector", "[ModelInputDataVector]")
{
	ModelOutputDataVectorTests tests;

	SECTION("Interface Tests")
	{
		tests.runTests();
	}
}