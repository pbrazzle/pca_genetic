#include "algorithm/GeneticAlgorithmParameters.hpp"

using PCAGenetic::GeneticAlgorithmParameters;
using GeneticJSON::JSONObject;

GeneticAlgorithmParameters::GeneticAlgorithmParameters() { }
			
JSONObject GeneticAlgorithmParameters::toJSON() const { return JSONObject("{ test : 0 }"); }
void GeneticAlgorithmParameters::fromJSON(const JSONObject& obj) { }