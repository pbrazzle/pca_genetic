#ifndef LOGISTIC_REGRESSION_MODEL
#define LOGISTIC_REGRESSION_MODEL

#include "model/GeneticModel.hpp"

namespace PCAGenetic
{
	//TODO implement this
	class LogisticRegressionModel : public GeneticModel
	{
		public:
			std::unique_ptr<GeneticModel> clone() const;
			
			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);
		
			std::vector<double> getParameters() const;
			void setParameters(std::vector<double>);
	};
}

#endif