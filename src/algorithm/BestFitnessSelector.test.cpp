#include "algorithm/ParentSelector.test.hpp"

#include "BestFitnessSelector.hpp"

class BestFitnessSelectorTests : public ParentSelectorTests
{
public:
	PSPtr getTestPS() override { return std::make_unique<BestFitnessSelector>(BestFitnessSelector()); }
};

TEST_CASE("BestFitnessSelector", "[BestFitnessSelector]")
{
	BestFitnessSelectorTests tests;

	SECTION("Interface tests")
	{
		tests.runTests();
	}
}