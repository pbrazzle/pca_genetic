#ifndef MODELOUTPUTDATA
#define MODELOUTPUTDATA

namespace PCAGenetic
{
	class ModelOutputData
	{
		public:
			virtual ~ModelOutputData = 0;
			
			//Returns a double representing the distance between 2 model outputs
			virtual double distance(ModelOutputData&) = 0;
	};
}

#endif