#include "algorithm/GeneticAlgorithm.hpp"
#include "model/LinearGeneticModel.hpp"
#include "model/ModelInputDataVector.hpp"
#include "model/ModelOutputDataVector.hpp"
#include "algorithm/GeneticAlgorithmFactory.hpp"

#include <iostream>

using PCAGenetic::GeneticAlgorithm;
using PCAGenetic::makeBasicAlgorithm;
using PCAGenetic::LinearGeneticModel;
using PCAGenetic::GeneticModel;
using PCAGenetic::ModelInputDataVector;
using PCAGenetic::ModelInputData;
using PCAGenetic::ModelOutputDataVector;
using PCAGenetic::ModelOutputData;

//Create a BasicGeneticAlgorithm with a LinearGeneticModel
//Optimize to 3x3 identity matrix
int main()
{
	GeneticAlgorithm geneticAlg = makeBasicAlgorithm();

	LinearGeneticModel templateModel(3);

	std::vector<double> vals = {1.0, 1.0, 1.0};
	ModelInputDataVector sampleInput(vals);
	ModelOutputDataVector sampleOutput(vals);

	PCAGenetic::trainingItem item;
	item.first = std::unique_ptr<ModelInputData>(new ModelInputDataVector(vals));
	item.second = std::unique_ptr<ModelOutputData>(new ModelOutputDataVector(vals));

	std::vector<PCAGenetic::trainingItem> trainingData;
	trainingData.emplace_back(std::move(item));

	geneticAlg.train(templateModel, std::move(trainingData), 500);

	std::unique_ptr<GeneticModel> optimizedModel = geneticAlg.getBestModel();

	std::unique_ptr<ModelOutputData> optimizedOutput = optimizedModel->evaluate(sampleInput);
	std::vector<double> optimizedVals = optimizedOutput->getData();

	std::cout << "Optimized output: " << optimizedVals[0] << ", " << optimizedVals[1] << ", " << optimizedVals[2] << '\n';

	return 0;
}
