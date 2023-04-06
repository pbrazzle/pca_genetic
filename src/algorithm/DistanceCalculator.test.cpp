#include "algorithm/FitnessCalculator.test.hpp"
#include "DistanceCalculator.hpp"

class DistanceCalculatorTests : public FitnessCalculatorTests
{
public:
	FCPtr getTestFC() { return std::make_unique<DistanceCalculator>(DistanceCalculator()); }
};

TEST_CASE("DistanceCalculator", "[DistanceCalculator]")
{
	DistanceCalculatorTests tests;

	SECTION("Interface tests")
	{
		tests.runTests();
	}
}
