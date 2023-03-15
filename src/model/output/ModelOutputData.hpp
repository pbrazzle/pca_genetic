#ifndef MODELOUTPUTDATA
#define MODELOUTPUTDATA

#include <memory>
#include <vector>

namespace GeneticModels
{
	class ModelOutputData
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
