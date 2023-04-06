#pragma once

#include <catch2/catch_test_macros.hpp>

#include "ParentSelector.hpp"

using namespace PCAGenetic;
using namespace JSON_IO;

class ParentSelectorTests
{
public:
	typedef std::unique_ptr<ParentSelector> PSPtr;

	virtual ~ParentSelectorTests() = default;

	virtual PSPtr getTestPS() = 0;

	void serializable()
	{
		PSPtr ps = getTestPS();

		JSONObject obj = ps->toJSON();

		REQUIRE(obj);
		REQUIRE(obj["typename"]);
	}

	void runTests()
	{
		SECTION("Serializable", "[ParentSelector]")
		{
			serializable();
		}
	}
};
