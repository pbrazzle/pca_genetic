#include "algorithm/ParentCombiner.test.hpp"

#include "RandomCrossingCombiner.hpp"

class RandomCrossingCombinerTests : public ParentCombinerTests
{
public:
	PCPtr getTestPC() override { return std::make_unique<RandomCrossingCombiner>(RandomCrossingCombiner()); }
};

TEST_CASE("RandomCrossingCombiner", "[RandomCrossingCombiner]")
{
	RandomCrossingCombinerTests tests;

	SECTION("Interface Tests")
	{
		tests.runTests();
	}
}
