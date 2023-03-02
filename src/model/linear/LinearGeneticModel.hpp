#ifndef LINEAR_GENETIC_MODEL
#define LINEAR_GENETIC_MODEL

#include "model/GeneticModel.hpp"

#include <string>

namespace PCAGenetic
{
	class LinearGeneticModel : public GeneticModel
	{
		private:
			int dataLength;
			std::vector<double> parameters;

		public:
			//Constructs a linear model for the provided data length
			//All parameters are initialized to 0
			LinearGeneticModel(int);

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
	};
}

#endif


