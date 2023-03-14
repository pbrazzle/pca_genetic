#include "algorithm/GeneticAlgorithmParameters.hpp"

using PCAGenetic::GeneticAlgorithmParameters;
using GeneticJSON::JSONObject;

GeneticAlgorithmParameters::GeneticAlgorithmParameters() { }
			
JSONObject GeneticAlgorithmParameters::toJSON() const 
{
	JSONObject paramObj;
	paramObj.addInt("generationSize", generationSize);
	paramObj.addFloat("mutationChance", mutationChance);
	paramObj.addFloat("mutationSize", mutationSize);
	paramObj.addFloat("paramRange", paramRange);
	paramObj.addFloat("elitism", elitism);
	
	return paramObj;
}
void GeneticAlgorithmParameters::fromJSON(const JSONObject& obj) { }