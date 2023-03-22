#include "model/downsample/DownSamplingModel.hpp"
#include "model/input/ModelInputDataVector.hpp"

#include <cassert>

using namespace GeneticModels;

void test2by2()
{
    DownSamplingModel simpleSampler(2, 2, 2, 2);

    ModelInputDataVector testInput({1, 2, 3, 4});
    auto result = simpleSampler.evaluate(testInput);
    auto resultData = result->getData();

    assert(resultData.size() == 1);
    assert(resultData[0] == 4);
}

void testPoolSizeMismatch()
{
    DownSamplingModel mismatch(2, 2, 3, 3);

    ModelInputDataVector testInput({1, 2, 3, 1, 2, 3, 1, 2, 3});
    auto result = mismatch.evaluate(testInput);
    auto resultData = result->getData();

    assert(resultData.size() == 4);
    assert(resultData[0] == 2);
    assert(resultData[1] == 3);
    assert(resultData[2] == 2);
    assert(resultData[3] == 3);
}

int main()
{
    test2by2();
    testPoolSizeMismatch();
    return 0;
}