#include "algorithm/ParentSelector.test.hpp"

#include "FitnessSumSelector.hpp"

class FitnessSumSelectorTests : public ParentSelectorTests
{
public:
	PSPtr getTestPS() override { return std::make_unique<FitnessSumSelector>(FitnessSumSelector()); }
};

TEST_CASE("FitnessSumSelector", "[FitnessSumSelector]")
{
	FitnessSumSelectorTests tests;

	SECTION("Interface tests")
	{
		tests.runTests();
	}
}