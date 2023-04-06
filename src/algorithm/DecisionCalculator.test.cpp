#pragma once

#include "algorithm/FitnessCalculator.test.hpp"
#include "DecisionCalculator.hpp"

class DecisionCalculatorTests : public FitnessCalculatorTests
{
public:
	FCPtr getTestFC() { return std::make_unique<DecisionCalculator>(DecisionCalculator()); }
};

TEST_CASE("DecisionCalculator", "[DecisionCalculator]")
{
	DecisionCalculatorTests tests;

	SECTION("Interface tests")
	{
		tests.runTests();
	}
}
