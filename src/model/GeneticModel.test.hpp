#pragma once

#include "GeneticModel.hpp"

#include <cstdlib>
#include <iostream>
#include <catch2/catch_test_macros.hpp>

namespace GeneticModels
{
	
using namespace JSON_IO;
	
class GeneticModelTests
{
	public:
		typedef std::unique_ptr<GeneticModel> ModelPtr;
	
		virtual std::unique_ptr<GeneticModel> createModel() = 0;
		
		void test(bool result)
		{
			if (!result) exit(1);
		}
		
		void offsetCloneDistance()
		{
			ModelPtr model = createModel();

			ModelPtr copy = model->copyWithOffset(1.0);
			
			auto modelParams = model->getParameters(), copyParams = copy->getParameters();
			for (int i = 0; i < modelParams.size(); i++)
			{
				REQUIRE(modelParams[i]-copyParams[i] <= 1.0);
			}
		}
		
		void testCloneParameterLength()
		{
			std::cout << "Testing Clone Parameter Length...\n";
			ModelPtr model = createModel();
			ModelPtr copy = model->clone();
			
			test(model->getParameters().size() == copy->getParameters().size());
		}
		
		void serializable()
		{
			ModelPtr model = createModel();
			
			JSONObject obj = model->toJSON();
			
			REQUIRE(obj);
			REQUIRE(obj["typename"]);
		}
};
}

std::unique_ptr<GeneticModels::GeneticModelTests> getTestClass();

TEST_CASE("GeneticModel is serializable", "[GeneticModel]")
{
	auto testClass = getTestClass();
	testClass->serializable();
}

TEST_CASE("GeneticModel offset clone within max distance", "[GeneticModel]")
{
	auto testClass = getTestClass();
	testClass->offsetCloneDistance();
}