#ifndef MODELOUTPUTDATA
#define MODELOUTPUTDATA

#include <memory>
#include <vector>

#include "json/JSONSerializable.hpp"

namespace GeneticModels
{
	using namespace GeneticJSON;
	
	class ModelOutputData : public JSONSerializable
	{
		public:
			virtual ~ModelOutputData() { }

			virtual std::unique_ptr<ModelOutputData> clone() const = 0;

			//Returns a double representing the distance between 2 model outputs
			virtual double distance(ModelOutputData&) = 0;

			//Returns a vector representation of the data
			virtual std::vector<double> getData() = 0;
	};
}

#endif
