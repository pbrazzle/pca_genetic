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
	std::cout << "Basic Algorithm test: 3x3 identity matrix\n";
	
	GeneticAlgorithm geneticAlg = makeBasicAlgorithm();
	geneticAlg.setParamRange(0.01);
	geneticAlg.setGenerationSize(100);
	std::cout << "Built BasicGeneticAlgorithm\n";

	LinearGeneticModel templateModel(3);
	templateModel.setParameters({1, 0, 0, 0, 1, 0, 0, 0, 1});
	std::cout << "Built LinearGeneticModel as template\n";
	std::cout << templateModel.printMatrix();

	std::vector<double> vals = {1.0, 1.0, 1.0};
	ModelInputDataVector sampleInput(vals);
	ModelOutputDataVector sampleOutput(vals);

	PCAGenetic::trainingItem item;
	item.first = std::unique_ptr<ModelInputData>(new ModelInputDataVector(vals));
	item.second = std::unique_ptr<ModelOutputData>(new ModelOutputDataVector(vals));
	std::cout << "Built training data\n";

	std::vector<PCAGenetic::trainingItem> trainingData;
	trainingData.emplace_back(std::move(item));

	geneticAlg.train(templateModel, std::move(trainingData), 0);
	for (int i = 0; i < 10; i++)
	{
		geneticAlg.continueTraining(10);

		std::unique_ptr<GeneticModel> optimizedModel = geneticAlg.getBestModel();
		LinearGeneticModel linModel = *((LinearGeneticModel*) optimizedModel.get());

		std::unique_ptr<ModelOutputData> optimizedOutput = optimizedModel->evaluate(sampleInput);
		double distance = optimizedOutput->distance(sampleOutput);
		std::cout << "Lowest Distance :" << distance << '\n';
		std::cout << linModel.printMatrix();
	}

	return 0;
}
