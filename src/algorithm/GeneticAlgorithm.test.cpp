#include "algorithm/GeneticAlgorithm.hpp"

#include <iostream>
#include <cassert>

using namespace PCAGenetic;
using namespace GeneticJSON;

void printAlgJSON()
{
    GeneticAlgorithm alg;
    std::cout << alg.toJSON().asJSON() << '\n';
}

void serializable()
{
    GeneticAlgorithm alg;

    JSONObject serialData = alg.toJSON();

    //Assert top level object
    assert(serialData);

    //Assert numerical parameters are serialized
    assert(serialData["generationSize"]);
    assert(serialData["offsetSize"]);
    assert(serialData["mutationSize"]);
    assert(serialData["mutationChance"]);
    assert(serialData["elitism"]);

    //Assert strategies are serialized
    assert(serialData["FitnessCalculator"]);
    assert(serialData["ParentSelector"]);
    assert(serialData["ParentCombiner"]);
}

int main()
{
    printAlgJSON();
    serializable();
    return 0;
}