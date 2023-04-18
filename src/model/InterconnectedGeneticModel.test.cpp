#include "GeneticModel.test.hpp"
#include "InterconnectedGeneticModel.hpp"
#include "LinearGeneticModel.hpp"

using namespace GeneticModels;

class InterconnectedModelTests : public GeneticModelTests
{
public:
	std::unique_ptr<GeneticModel> createModel() override { return getTestModel(); }

	ModelPtr getTestModel() override
	{
		std::vector<ModelPtr> layer1;
		layer1.emplace_back(std::make_unique<LinearGeneticModel>(3, std::vector<double>({1, 0, 0, 0, 1, 0, 0, 0, 1})));
		std::vector<ModelPtr> layer2;
		layer2.emplace_back(std::make_unique<LinearGeneticModel>(3, std::vector<double>({ 1, 0, 0, 0, 1, 0, 0, 0, 1 })));
		std::vector<std::vector<ModelPtr>> allLayers;
		allLayers.emplace_back(std::move(layer1));
		allLayers.emplace_back(std::move(layer2));

		return std::make_unique<InterconnectedGeneticModel>(allLayers);
	}

	ModelPtr getBlankModel() override { return std::make_unique<InterconnectedGeneticModel>(); }
};

TEST_CASE("InterconnectedGeneticModel", "[InterconnectedGeneticModel]")
{
	InterconnectedModelTests testClass;

	SECTION("Interface Tests")
	{
		testClass.runTests();
	}
}