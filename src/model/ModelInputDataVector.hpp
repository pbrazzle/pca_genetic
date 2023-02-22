#ifndef MODELINPUTDATAVECTOR
#define MODELINPUTDATAVECTOR

#include "ModelInputData.hpp"

namespace PCAGenetic
{
	class ModelInputDataVector : public ModelInputData
	{
		private:
			std::vector<double> data;

		public:
			ModelInputDataVector(std::vector<double>);

			std::vector<double> getData();			
	};
}

#endif
