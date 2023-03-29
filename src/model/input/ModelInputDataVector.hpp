#ifndef MODELINPUTDATAVECTOR
#define MODELINPUTDATAVECTOR

#include "model/input/ModelInputData.hpp"
#include <memory>

namespace GeneticModels
{
	using namespace JSON_IO;
	
	class ModelInputDataVector : public ModelInputData
	{
		private:
			std::vector<double> data;

		public:
			ModelInputDataVector(std::vector<double>);

			std::unique_ptr<ModelInputData> clone() const;

			std::vector<double> getData();	

			JSONObject toJSON() const;
			void fromJSON(const JSONObject& obj);	
	};
}

#endif
