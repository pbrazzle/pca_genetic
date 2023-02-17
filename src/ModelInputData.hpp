#ifndef MODELINPUTDATA
#define MODELINPUTDATA

#include <vector>

namespace PCAGenetic
{
	class ModelInputData
	{
		public:
			virtual ~ModelInputData() { }

			//Returns a vector representation of the input data
			virtual std::vector<double> getData() = 0;
	};
}

#endif
