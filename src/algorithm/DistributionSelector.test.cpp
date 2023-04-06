#include "algorithm/ParentSelector.test.hpp"

#include "DistributionSelector.hpp"

class DistributionSelectorTests : public ParentSelectorTests
{
public:
	PSPtr getTestPS() override { return std::make_unique<DistributionSelector>(DistributionSelector()); }
};

TEST_CASE("DistributionSelector", "[DistributionSelector]")
{
	DistributionSelectorTests tests;

	SECTION("Interface tests")
	{
		tests.runTests();
	}
}
