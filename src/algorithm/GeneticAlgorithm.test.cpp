#include "GeneticAlgorithm.hpp"
#include "GeneticAlgorithmFactory.hpp"

#include <iostream>
#include <cassert>

using namespace PCAGenetic;
using namespace JSON_IO;

void printAlgJSON()
{
    GeneticAlgorithm alg = makeBasicAlgorithm();
    std::cout << alg.toJSON().asJSON() << '\n';
}

void serializable()
{
    GeneticAlgorithm alg = makeBasicAlgorithm();

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