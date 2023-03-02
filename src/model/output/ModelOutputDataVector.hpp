#ifndef MODELOUTPUTDATAVECTOR
#define MODELOUTPUTDATAVECTOR

#include "model/output/ModelOutputData.hpp"
#include <memory>

namespace PCAGenetic
{
	class ModelOutputDataVector : public ModelOutputData
	{
		private:
			std::vector<double> data;
		public:
			ModelOutputDataVector(std::vector<double>);

			std::unique_ptr<ModelOutputData> clone() const;

			double distance(ModelOutputData&);

			std::vector<double> getData();
	};
}

#endif

