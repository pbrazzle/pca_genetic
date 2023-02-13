#ifndef GENETIC_MODEL 
#define GENETIC_MODEL

#include <functional>
#include <array>

namespace PCAGenetic
{
	template <typename T, int numParams>
	class GeneticModel
	{
		typedef std::function<T(std::array<T,numParams>)> modelFunc;
		
		private:
			
		public:
			GeneticModel();
		
			//Trains the model with the provided fitness function
			//Runs the provided number of generations
			void train(modelFunc fitnessFunc, int generations);
			
			//Calculates the result of the given function using the best available solution
			T calculateFunc(modelFunc func);
	};
}

#include "GeneticModel.tpp"

#endif