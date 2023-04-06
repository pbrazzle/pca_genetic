#pragma once

#include <catch2/catch_test_macros.hpp>

#include "ModelInputData.hpp"

class ModelInputDataTests
{
public:
	typedef std::unique_ptr<GeneticModels::ModelInputData> DataPtr;

	virtual DataPtr getTestData() = 0;
	virtual DataPtr getBlankData() = 0;

	void serializable()
	{
		DataPtr data = getTestData();

		JSON_IO::JSONObject obj = data->toJSON();

		REQUIRE(obj);
		REQUIRE(obj["typename"]);
	}

	void readsJSON()
	{
		DataPtr data = getTestData();
		DataPtr blank = getBlankData();

		blank->fromJSON(data->toJSON()["data"]);

		auto dataVals = data->getData(), blankVals = blank->getData();

		REQUIRE(dataVals.size() == blankVals.size());
		for (int i = 0; i < dataVals.size(); i++)
		{
			REQUIRE(dataVals[i] == blankVals[i]);
		}
	}

	void runTests()
	{
		SECTION("Serializable")
		{
			serializable();
		}
		SECTION("Reads JSON")
		{
			readsJSON();
		}
	}
};
