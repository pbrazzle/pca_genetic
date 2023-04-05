#include "DownSamplingModel.hpp"
#include "ModelOutputDataVector.hpp"

#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace GeneticModels;

DownSamplingModel::DownSamplingModel(int pool_width, int pool_height, int image_width, int image_height) :
	pool_size(pool_width, pool_height), image_size(image_width, image_height)
{
}

DownSamplingModel::DownSamplingModel(std::pair<int, int> ps, std::pair<int, int> is) : pool_size(ps), image_size(is)
{
}

std::unique_ptr<GeneticModel> DownSamplingModel::clone() const
{
	return std::make_unique<DownSamplingModel>(pool_size, image_size);
}

std::vector<double> DownSamplingModel::getPool(const std::vector<double>& image, int offset)
{
	std::vector<double> pool;

	int pool_width = pool_size.first;
	int remaining_edge = image_size.first - offset % image_size.first;
	if (remaining_edge < pool_size.first)
		pool_width = remaining_edge;

	int pool_height = pool_size.second;
	remaining_edge = image_size.second - offset / image_size.first;
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

	int horizontal_pools = static_cast<int>(std::ceil((double)image_size.first / pool_size.first));
	int vertical_pools = static_cast<int>(std::ceil((double)image_size.second / pool_size.second));

	for (int i = 0; i < vertical_pools; i++)
	{
		for (int j = 0; j < horizontal_pools; j++)
		{
			pools.push_back(getPool(image, j * pool_size.first + i * image_size.first * pool_size.second));
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
	if (image.size() != image_size.first * image_size.second) throw std::invalid_argument("Invalid image size");

	auto pools = reorderByPools(image);
	return std::make_unique<ModelOutputDataVector>(maxPool(pools));
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
	return image_size.first*image_size.second;
}

int DownSamplingModel::getOutputDataLength() const
{
	const int horizontal_pools = static_cast<int>(std::ceil((double)image_size.first / pool_size.first));
	const int vertical_pools = static_cast<int>(std::ceil((double)image_size.second / pool_size.second));
	return horizontal_pools * vertical_pools;
}

JSONObject DownSamplingModel::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "DownSamplingModel");

	JSONObject paramObj;
	paramObj.addInt("pool_width", pool_size.first);
	paramObj.addInt("pool_height", pool_size.second);
	paramObj.addInt("image_width", image_size.first);
	paramObj.addInt("image_height", image_size.second);

	obj.addObject("data", paramObj);
	return obj;
}

void DownSamplingModel::fromJSON(const JSONObject& obj)
{
	pool_size.first = obj["pool_width"].asInt();
	pool_size.second = obj["pool_height"].asInt();
	image_size.first = obj["image_width"].asInt();
	image_size.second = obj["image_height"].asInt();
}
