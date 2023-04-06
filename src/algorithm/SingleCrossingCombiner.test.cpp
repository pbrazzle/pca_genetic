#include "algorithm/ParentCombiner.test.hpp"

#include "SingleCrossingCombiner.hpp"

class SingleCrossingCombinerTests : public ParentCombinerTests
{
public:
	PCPtr getTestPC() override { return std::make_unique<SingleCrossingCombiner>(SingleCrossingCombiner()); }
};

TEST_CASE("SingleCrossingCombiner", "[SingleCrossingCombiner]")
{
	SingleCrossingCombinerTests tests;

	SECTION("Interface Tests")
	{
		tests.runTests();
	}
}