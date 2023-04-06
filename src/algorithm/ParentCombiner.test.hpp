#pragma once

#include <catch2/catch_test_macros.hpp>

#include "ParentCombiner.hpp"

using namespace PCAGenetic;
using namespace JSON_IO;

class ParentCombinerTests
{
public:
	typedef std::unique_ptr<ParentCombiner> PCPtr;
	virtual PCPtr getTestPC() = 0;

	void serializable()
	{
		PCPtr pc = getTestPC();
		JSONObject obj = pc->toJSON();

		REQUIRE(obj);
		REQUIRE(obj["typename"]);
	}

	void resultIsSameSize()
	{
		PCPtr pc = getTestPC();
		auto result = pc->combineParameters({ 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5 });

		REQUIRE(result.size() == 5);
	}

	void runTests()
	{
		SECTION("Serializable")
		{
			serializable();
		}
		SECTION("Result is correct size")
		{
			resultIsSameSize();
		}
	}
};
