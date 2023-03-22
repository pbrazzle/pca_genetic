#include "algorithm/GeneticAlgorithm.hpp"

#include <iostream>

using namespace PCAGenetic;

void printAlgJSON()
{
    GeneticAlgorithm alg;
    std::cout << alg.toJSON().asJSON() << '\n';
}

int main()
{
    printAlgJSON();
    return 0;
}