#include "GenerationCreator.hpp"

using namespace PCAGenetic;
using namespace GeneticModels;

GenerationCreator::GenerationCreator(double o,int g) : offsetSize(o), generationSize(g) { }
			
ModelHandle createModel(const GeneticModel& modelTemplate, double offsetSize)
{
	ModelHandle newModel(modelTemplate.clone());
	
	std::vector<double> params = newModel->getParameters();
	for (int i = 0; i < params.size(); i++)
	{
		params[i] += offsetSize*(2*((double) rand() / RAND_MAX) - 1);
	}
	newModel->setParameters(params);
	return newModel;
}
			
std::vector<ModelHandle> GenerationCreator::create(const GeneticModel& modelTemplate)
{
	std::vector<ModelHandle> generation;
	generation.reserve(generationSize);
	
	for (int i = 0; i < generationSize; i++)
	{
		generation.push_back(createModel(modelTemplate, offsetSize));
	}
	
	return generation;
}

void GenerationCreator::setOffsetSize(double o) { offsetSize = o; }
void GenerationCreator::setGenerationSize(int g) { generationSize = g; }