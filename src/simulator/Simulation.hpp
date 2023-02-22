#ifndef SIMULATION
#define SIMULATION

#include "algorithm/GeneticAlgorithm.hpp"
#include "model/GeneticModel.hpp"
#include "GeneticTypes.hpp"

#include <memory>
#include <vector>
#include <string>

namespace PCAGenetic
{
	class Simulation
	{
		private:
			std::string name;
			GeneticAlgorithm alg;
			std::unique_ptr<GeneticModel> modelTemplate;
			std::vector<trainingItem> trainingData;
			int generations;

		public:
			Simulation(std::string n, GeneticAlgorithm a, std::unique_ptr<GeneticModel> m, std::vector<trainingItem> td, int g);
			Simulation(const Simulation& other);

			void run();
	};
}

#endif
