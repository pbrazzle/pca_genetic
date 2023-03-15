#include "algorithm/GeneticAlgorithmParameters.hpp"
#include "algorithm/GeneticAlgorithmFactory.hpp"

using namespace PCAGenetic;
using namespace GeneticJSON;

GeneticAlgorithmParameters::GeneticAlgorithmParameters() 
{ 
	generationSize = 0;
	mutationChance = 0;
	mutationSize = 0;
	paramRange = 0;
	elitism = 0;
	
	modelType = "";
	calcType = "";
	selectType = "";
	combType = "";
}

JSONObject GeneticAlgorithmParameters::toJSON() const 
{
	JSONObject paramObj;
	paramObj.addInt("generationSize", generationSize);
	paramObj.addFloat("mutationChance", mutationChance);
	paramObj.addFloat("mutationSize", mutationSize);
	paramObj.addFloat("paramRange", paramRange);
	paramObj.addFloat("elitism", elitism);
	
	paramObj.addString("modelType", modelType);
	paramObj.addString("calcType", calcType);
	paramObj.addString("selectType", selectType);
	paramObj.addString("combType", combType);
	
	return paramObj;
}
void GeneticAlgorithmParameters::fromJSON(const JSONObject& obj) 
{ 
	generationSize = obj["generationSize"].asInt();
	mutationChance = obj["mutationChance"].asFloat();
	mutationSize = obj["mutationSize"].asFloat();
	paramRange = obj["paramRange"].asFloat();
	elitism = obj["elitism"].asFloat();
	
	modelType = obj["modelType"].asString();
	calcType = obj["calcType"].asString();
	selectType = obj["selectType"].asString();
	combType = obj["combType"].asString();
	
	//TODO pass strategy data onto these
	fitnessCalc = fitCalcMap[calcType]();
	parentSelect = selectMap[selectType]();
	parentComb = combinerMap[combType]();
	
	//TODO make string -> model factory and pass data
}