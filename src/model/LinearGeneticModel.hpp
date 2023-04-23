#ifndef LINEAR_GENETIC_MODEL
#define LINEAR_GENETIC_MODEL

#include "GeneticModel.hpp"

#include <string>

namespace GeneticModels
{
	using namespace JSON_IO;
	
	class LinearGeneticModel : public GeneticModel
	{
		private:
			int dataLength, inputSize, outputSize;
			std::vector<double> parameters;

		public:
			LinearGeneticModel() = default;

			//Constructs a linear model for the provided data length
			//All parameters are initialized to 0
			LinearGeneticModel(int);

			LinearGeneticModel(int, int);

			LinearGeneticModel(int, int, std::vector<double>);

			//Constructs a linear model for the provided data length
			//Parameters are initialized to the provided vector
			//If the vector is not the correct length, throws a std::invalid_argument exception
			LinearGeneticModel(int, std::vector<double>);

			//Returns a pointer to a deep copy of the model
			std::unique_ptr<GeneticModel> clone() const;

			//Calculates the result of the matrix vector multiplication between
			//the model parameters and the input data
			//Returns the output as a ModelOutputDataVector
			std::unique_ptr<ModelOutputData> evaluate(ModelInputData&);

			//Returns the model parameters as a vector in row order
			std::vector<double> getParameters() const;

			//Sets the model parameters to the provided vector in row order
			//Throws a std::invaild_argument exception if the vector is not the same length
			//as the current model parameters
			void setParameters(std::vector<double>);

			//Returns a string representation of the model parameters in matrix form
			std::string printMatrix() const;
			
			JSONObject toJSON() const override;
			void fromJSON(const JSONObject& obj);
			int getInputDataLength() const override;
			int getOutputDataLength() const override;
	};
}

#endif


