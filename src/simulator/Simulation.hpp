#ifndef SIMULATION
#define SIMULATION

#include "algorithm/GeneticAlgorithm.hpp"
#include "model/GeneticModel.hpp"
#include "GeneticTypes.hpp"
#include "json/JSONSerializable.hpp"

#include <memory>
#include <vector>
#include <string>

namespace GeneticSimulator
{
	using namespace PCAGenetic;
	using namespace JSON_IO;

	class Simulation : public JSONSerializable
	{
		private:
			std::string name;
			GeneticAlgorithm alg;
			std::unique_ptr<GeneticModel> modelTemplate;
			std::vector<trainingItem> trainingData;
			int generations;
			std::vector<double> generationTimes;

		public:
			Simulation() = default;
			Simulation(std::string n, GeneticAlgorithm a, std::unique_ptr<GeneticModel> m, std::vector<trainingItem> td, int g);
			Simulation(const Simulation& other);

			void run();
			
			JSONObject toJSON() const;
			void fromJSON(const JSONObject& obj);

			std::vector<double> getBestFitnesses();
			std::vector<double> getAvgFitnesses();
	};
}

#endif
