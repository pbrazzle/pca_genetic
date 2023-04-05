#include "DownSamplingModel.hpp"
#include "ModelOutputDataVector.hpp"

#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace GeneticModels;

DownSamplingModel::DownSamplingModel(int pool_width, int pool_height, int image_width, int image_height) : pool_size(pool_width, pool_height), image_size(image_width, image_height) { }

DownSamplingModel::DownSamplingModel(std::pair<int, int> ps, std::pair<int, int> is) : pool_size(ps), image_size(is) { }

std::unique_ptr<GeneticModel> DownSamplingModel::clone() const
{
	return std::unique_ptr<GeneticModel>(new DownSamplingModel(pool_size, image_size));
}

std::vector<double> DownSamplingModel::getPool(const std::vector<double>& image, int offset)
{
	std::vector<double> pool;

	int pool_width = pool_size.first;
	int remaining_edge = image_size.first - offset % image_size.first;
	if (remaining_edge < pool_size.first)
		pool_width = remaining_edge;

	int pool_height = pool_size.second;
	remaining_edge = image_size.second - offset/image_size.first;
	if (remaining_edge < pool_size.second)
		pool_height = remaining_edge;

	for (int i = 0; i < pool_height; i++)
	{
		pool.insert(pool.end(), image.begin() + offset, image.begin() + offset + pool_width);
		offset += image_size.first;
	}

	return pool;
}

std::vector<std::vector<double>> DownSamplingModel::reorderByPools(const std::vector<double>& image)
{
	std::vector<std::vector<double>> pools;

	int horizontal_pools = (int) std::ceil((double) image_size.first/pool_size.first);
	int vertical_pools = (int) std::ceil((double) image_size.second/pool_size.second);

	for (int i = 0; i < vertical_pools; i++)
	{
		for (int j = 0; j < horizontal_pools; j++)
		{
			pools.push_back(getPool(image, j*pool_size.first + i*image_size.first*pool_size.second));
		}
	}

	return pools;
}

std::vector<double> DownSamplingModel::maxPool(const std::vector<std::vector<double>>& pools)
{
	std::vector<double> maxPools;
	maxPools.reserve(pools.size());
	
	std::transform(pools.begin(), pools.end(), std::back_inserter(maxPools), [](std::vector<double> pool)
	{
		return *std::max_element(pool.begin(), pool.end());
	});

	return maxPools;
}
			
std::unique_ptr<ModelOutputData> DownSamplingModel::evaluate(ModelInputData& input)
{
	std::vector<double> image = input.getData();
	if (image.size() != image_size.first*image_size.second) throw std::invalid_argument("Invalid image size");

	auto pools = reorderByPools(image);
	return std::unique_ptr<ModelOutputData>(new ModelOutputDataVector(maxPool(pools)));
}

std::vector<double> DownSamplingModel::getParameters() const
{
	return std::vector<double>();
}

void DownSamplingModel::setParameters(std::vector<double>)
{
	
}

int DownSamplingModel::getInputDataLength() const
{
	return 0;
}

int DownSamplingModel::getOutputDataLength() const
{
	return 0;
}
