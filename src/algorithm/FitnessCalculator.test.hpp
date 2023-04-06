#pragma once

#include <catch2/catch_test_macros.hpp>

#include "FitnessCalculator.hpp"

using namespace PCAGenetic;
using namespace JSON_IO;

class FitnessCalculatorTests
{
public:
	typedef std::unique_ptr<FitnessCalculator> FCPtr;

	virtual FCPtr getTestFC() = 0;

	void serializable()
	{
		FCPtr fc = getTestFC();
		JSONObject obj = fc->toJSON();

		REQUIRE(obj);
		REQUIRE(obj["typename"]);
	}

	void runTests()
	{
		SECTION("Serializable", "[FitnessCalculator]")
		{
			serializable();
		}
	}
};
