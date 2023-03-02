#ifndef MODELINPUTDATAVECTOR
#define MODELINPUTDATAVECTOR

#include "model/ModelInputData.hpp"
#include <memory>

namespace PCAGenetic
{
	class ModelInputDataVector : public ModelInputData
	{
		private:
			std::vector<double> data;

		public:
			ModelInputDataVector(std::vector<double>);

			std::unique_ptr<ModelInputData> clone() const;

			std::vector<double> getData();			
	};
}

#endif
