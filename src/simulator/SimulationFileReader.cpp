#include "simulator/SimulationFileReader.hpp"

#include "algorithm/DistanceCalculator.hpp"
#include "algorithm/FitnessSumSelector.hpp"
#include "algorithm/SingleCrossingCombiner.hpp"
#include "model/LinearGeneticModel.hpp"
#include "model/ModelInputDataVector.hpp"
#include "model/ModelOutputDataVector.hpp"

#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
#include <iostream>

using PCAGenetic::SimulationFileReader;
using PCAGenetic::Simulation;
using PCAGenetic::GeneticAlgorithm;
using PCAGenetic::GeneticModel;
using PCAGenetic::trainingItem;
using PCAGenetic::FitnessCalculator;
using PCAGenetic::DistanceCalculator;
using PCAGenetic::ParentSelector;
using PCAGenetic::FitnessSumSelector;
using PCAGenetic::ParentCombiner;
using PCAGenetic::SingleCrossingCombiner;
using PCAGenetic::LinearGeneticModel;
using PCAGenetic::GeneticModel;
using PCAGenetic::ModelInputDataVector;
using PCAGenetic::ModelOutputDataVector;
using PCAGenetic::ModelInputData;
using PCAGenetic::ModelOutputData;

SimulationFileReader::SimulationFileReader() { }

std::unique_ptr<PCAGenetic::FitnessCalculator> makeFitnessCalc(std::string className)
{
	return std::unique_ptr<PCAGenetic::FitnessCalculator>(new DistanceCalculator());
}

std::unique_ptr<PCAGenetic::ParentSelector> makeParentSelect(std::string className)
{
	return std::unique_ptr<ParentSelector>(new FitnessSumSelector());
}

std::unique_ptr<PCAGenetic::ParentCombiner> makeParentComb(std::string className)
{
	return std::unique_ptr<PCAGenetic::ParentCombiner>(new SingleCrossingCombiner());
}

std::vector<double> readLineAsVector(std::ifstream&);

std::unique_ptr<GeneticModel> readModel(std::ifstream& file)
{
	std::string line;
	std::getline(file, line);
	std::getline(file, line);
	std::stringstream ss(line);
	int dataLength;
	ss >> dataLength;
	std::vector<double> startParams = readLineAsVector(file);
	return std::unique_ptr<GeneticModel>(new LinearGeneticModel(dataLength, startParams));
}

std::vector<double> readLineAsVector(std::ifstream& file)
{
	std::string line;
	std::getline(file, line);
	std::vector<double> data;

	std::cout << "Reading line " << line << " as vector\n";
	std::stringstream ss(line);
	while (std::getline(ss, line, ','))
	{
		std::stringstream l(line);
		double d;
		l >> d;
		data.push_back(d);
	}

	return data;
}

double readLineAsDouble(std::ifstream& file)
{
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	double d;
	ss >> d;
	return d;
}

std::vector<trainingItem> readTrainingData(std::ifstream& file)
{
	int dataSize;
	std::string line;
	std::getline(file, line);
	std::stringstream(line) >> dataSize;

	std::cout << "Reading " << dataSize << " items\n";
	std::vector<trainingItem> trainingData;

	for (int i = 0; i < dataSize; i++)
	{
		std::cout << "Item " << i << '\n';
		std::unique_ptr<PCAGenetic::ModelInputData> input(new ModelInputDataVector(readLineAsVector(file)));
		std::unique_ptr<ModelOutputData> output(new ModelOutputDataVector(readLineAsVector(file)));

		trainingData.emplace_back(trainingItem(std::move(input), std::move(output)));
	}

	return std::move(trainingData);
}

Simulation readNextSim(std::ifstream& file)
{
	std::string name;
	GeneticAlgorithm alg;
	std::unique_ptr<GeneticModel> modelTemplate;
	std::vector<trainingItem> trainingData;
	int generations;

	std::string line;
	
	//Read Sim name
	std::getline(file, line);
	name = line;
	std::cout << "Read Simulation name as " << name << '\n'; 

	//Read Parameters
	int generationSize;
	double mutationChance, mutationSize, paramRange;
	
	generationSize = readLineAsDouble(file);
	mutationChance = readLineAsDouble(file);
	mutationSize = readLineAsDouble(file);
	paramRange = readLineAsDouble(file);

	//Build Algorithm
	std::getline(file, line);
	std::unique_ptr<PCAGenetic::FitnessCalculator> fitCalc = makeFitnessCalc(line);
	std::getline(file, line);
	std::unique_ptr<PCAGenetic::ParentSelector> parentSelect = makeParentSelect(line);
	std::getline(file, line);
	std::unique_ptr<ParentCombiner> parentComb = makeParentComb(line);
	alg = GeneticAlgorithm(std::move(fitCalc), std::move(parentSelect), std::move(parentComb));
	std::cout << "Built simulation algorithm\n";

	alg.setGenerationSize(generationSize);
	alg.setMutationChance(mutationChance);
	alg.setMutationSize(mutationSize);
	alg.setParamRange(paramRange);
	std::cout << "Added simulation parameters\n";
	std::cout << "Gen Size: " << generationSize << '\n';
	std::cout << "Mut %: " << mutationChance << '\n';
	std::cout << "Mut Size: " << mutationSize << '\n';
	std::cout << "Start Range: " << paramRange << '\n';

	//Build Model
	modelTemplate = std::move(readModel(file));
	std::cout << "Built simulation model\n";

	//Read Training Data
	trainingData = std::move(readTrainingData(file));
	std::cout << "Read simulation training data\n";

	//Read # of generations
	std::getline(file, line);
	std::stringstream(line) >> generations;
	std::cout << "Read generation count: " << generations << '\n';

	return Simulation(name, alg, std::move(modelTemplate), std::move(trainingData), generations);
}

std::vector<Simulation> SimulationFileReader::readSimulations(std::string filename)
{
	std::ifstream simFile(filename);

	std::vector<Simulation> sims;
	while (!simFile.eof()) 
	{
		sims.push_back(readNextSim(simFile));
		
		while (simFile.peek() == '\n') simFile.get();
	}

	return sims;
}
