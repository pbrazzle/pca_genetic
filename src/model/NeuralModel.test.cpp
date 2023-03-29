#include <cassert>

#include "NeuralModel.hpp"
#include "ModelInputDataVector.hpp"

using namespace GeneticModels;

void testIdentityNetwork()
{
    NeuralModel identity({1});
    ModelInputDataVector testInput({1});

    auto result = identity.evaluate(testInput);

    auto resultData = result->getData();
    assert(resultData.size() == 1);
    assert(resultData[0] == 1);
}

void testSingleWeightNetwork()
{
    NeuralModel identity({1, 1}, {2});
    ModelInputDataVector testInput({1});

    auto result = identity.evaluate(testInput);

    auto resultData = result->getData();
    assert(resultData.size() == 1);
    assert(resultData[0] == 2);
}

void testMultiNodeNetwork()
{
    NeuralModel identity({1, 3}, {1, 2, 3});
    ModelInputDataVector testInput({1});

    auto result = identity.evaluate(testInput);

    auto resultData = result->getData();
    assert(resultData.size() == 3);
    assert(resultData[0] == 1);
    assert(resultData[1] == 2);
    assert(resultData[2] == 3);
}

void testMultiLayerNetwork()
{
    NeuralModel identity({1, 3, 3}, {1, 2, 3,
                                     1, 2, 3,
                                     1, 2, 3,
                                     1, 2, 3});
    ModelInputDataVector testInput({1});

    auto result = identity.evaluate(testInput);

    auto resultData = result->getData();
    assert(resultData.size() == 3);
    assert(resultData[0] == 14);
    assert(resultData[1] == 14);
    assert(resultData[2] == 14);
}

int main()
{
    testIdentityNetwork();
    testSingleWeightNetwork();
    testMultiNodeNetwork();
    testMultiLayerNetwork();
    return 0;
}