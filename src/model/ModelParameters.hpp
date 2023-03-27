#ifndef MODEL_PARAMETERS
#define MODEL_PARAMETERS

namespace GeneticModels
{
	class ModelParameters
	{
		private:
			std::vector<double> params;
			
		public:
			ModelParameters() = default;
			ModelParameters(int);
			
			std::vector<double> getParams() const;
			void setParams(const std::vector<double>&);
	};
}

#endif