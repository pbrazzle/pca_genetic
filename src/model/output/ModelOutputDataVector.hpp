#ifndef MODELOUTPUTDATAVECTOR
#define MODELOUTPUTDATAVECTOR

#include "model/output/ModelOutputData.hpp"
#include <memory>

namespace GeneticModels
{
	using namespace JSON_IO;
	
	class ModelOutputDataVector : public ModelOutputData
	{
		private:
			std::vector<double> data;
		public:
			ModelOutputDataVector(std::vector<double>);

			std::unique_ptr<ModelOutputData> clone() const;

			double distance(ModelOutputData&);

			std::vector<double> getData();
			
			JSONObject toJSON() const;
			void fromJSON(const JSONObject& obj);
	};
}

#endif

