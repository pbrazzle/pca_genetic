#ifndef MODELOUTPUTDATAVECTOR
#define MODELOUTPUTDATAVECTOR

#include "ModelOutputData.hpp"

namespace PCAGenetic
{
	class ModelOutputDataVector : public ModelOutputData
	{
		private:
			std::vector<double> data;
		public:
			ModelOutputDataVector(std::vector<double>);

			double distance(ModelOutputData&);

			std::vector<double> getData();
	};
}

#endif

