#pragma once

#include "GeneticModel.hpp"
#include "ModelInputDataVector.hpp"

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

		virtual ModelPtr getTestModel() = 0;
		virtual ModelPtr getBlankModel() = 0;

		void testModelIsNotEmpty()
		{
			ModelPtr model = getTestModel();

			REQUIRE(model->getInputDataLength() != 0);
			REQUIRE(model->getOutputDataLength() != 0);
		}

		void modelResultSizeCorrect()
		{
			ModelPtr model = getTestModel();

			std::vector<double> inputVec(model->getInputDataLength(), 0.0);
			ModelInputDataVector inputData(inputVec);

			auto result = model->evaluate(inputData);

			REQUIRE(result->getData().size() == model->getOutputDataLength());
		}
		
		void offsetCloneDistance()
		{
			ModelPtr model = createModel();

			ModelPtr copy = model->copyWithOffset(1.0);
			
			auto modelParams = model->getParameters(), copyParams = copy->getParameters();

			REQUIRE(modelParams.size() == copyParams.size());
			for (int i = 0; i < modelParams.size(); i++)
			{
				REQUIRE(modelParams[i]-copyParams[i] <= 1.0);
			}
		}
		
		void cloneHasEqualParameterLength()
		{
			ModelPtr model = createModel();
			ModelPtr copy = model->clone();
			
			REQUIRE(model->getParameters().size() == copy->getParameters().size());
		}

		void cloneHasEqualParameters()
		{
			ModelPtr model = createModel();
			ModelPtr copy = model->clone();

			auto modelParams = model->getParameters();
			auto copyParams = copy->getParameters();

			REQUIRE(modelParams.size() == copyParams.size());

			for (int i = 0; i < modelParams.size(); i++)
			{
				REQUIRE(modelParams[i] == copyParams[i]);
			}
		}

		void cloneHasEqualDataSize()
		{
			ModelPtr model = createModel();
			ModelPtr copy = model->clone();

			REQUIRE(model->getInputDataLength() == copy->getInputDataLength());
			REQUIRE(model->getOutputDataLength() == copy->getOutputDataLength());
		}
		
		void serializable()
		{
			ModelPtr model = createModel();
			
			JSONObject obj = model->toJSON();
			
			REQUIRE(obj);
			REQUIRE(obj["typename"]);
			//REQUIRE(obj["data"]);
		}

		void buildsMutationFromJSON()
		{
			ModelPtr model = createModel();
			ModelPtr mutatedModel = model->clone();
			mutatedModel->mutate(1, 0.01);

			JSONObject mutatedJSON = mutatedModel->toJSON();
			model->fromJSON(mutatedJSON["data"]);

			auto modelParams = model->getParameters(), mutatedParams = mutatedModel->getParameters();
			for (int i = 0; i < modelParams.size(); i++)
			{
				REQUIRE(modelParams[i] == mutatedParams[i]);
			}
		}

		void buildsBlankFromJSON()
		{
			auto model = getTestModel();
			auto blankModel = getBlankModel();

			blankModel->fromJSON(model->toJSON()["data"]);

			REQUIRE(model->getInputDataLength() == blankModel->getInputDataLength());
			REQUIRE(model->getOutputDataLength() == blankModel->getOutputDataLength());

			auto modelParams = model->getParameters(), blankParams = blankModel->getParameters();

			REQUIRE(modelParams.size() == blankParams.size());
			for (int i = 0; i < modelParams.size(); i++)
			{
				REQUIRE(modelParams[i] == blankParams[i]);
			}
		}
		
		void runTests()
		{
			SECTION("Test model is not empty")
			{
				testModelIsNotEmpty();
			}
			SECTION("Offset clone within max distance")
			{
				offsetCloneDistance();
			}
			SECTION("Result size is correct")
			{
				modelResultSizeCorrect();
			}
			SECTION("Clone has equal parameters")
			{
				cloneHasEqualParameters();
			}
			SECTION("Clone has equal data size")
			{
				cloneHasEqualDataSize();
			}
			SECTION("Serializable")
			{
				serializable();
			}
			SECTION("Reads JSON")
			{
				buildsMutationFromJSON();
				buildsBlankFromJSON();
			}
		}
};
}