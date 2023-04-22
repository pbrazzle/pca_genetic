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

double DownSamplingModel::maxPool(const std::vector<double>& image, const int& offset)
{
	int pool_width = pool_size.first;
	int remaining_edge = image_size.first - offset % image_size.first;
	if (remaining_edge < pool_size.first)
		pool_width = remaining_edge;

	int pool_height = pool_size.second;
	remaining_edge = image_size.second - offset / image_size.first;
	if (remaining_edge < pool_size.second)
		pool_height = remaining_edge;

	double max = 0.0;
	for (int i = 0; i < pool_height; i++)
	{
		for (int j = 0; j < pool_width; j++)
		{
			if (image[offset + j + image_size.first * i] > max) max = image[offset + j + image_size.first * i];
		}
	}

	return max;
}

std::unique_ptr<ModelOutputData> DownSamplingModel::evaluate(ModelInputData& input)
{
	std::vector<double> image = input.getData();
	if (image.size() != image_size.first * image_size.second) throw std::invalid_argument("Invalid image size");

	const int horizontal_pools = (image_size.first / pool_size.first) + ((image_size.first % pool_size.first) ? 1 : 0);
	const int vertical_pools = (image_size.second / pool_size.second) + ((image_size.second % pool_size.second) ? 1 : 0);
	std::vector<double> poolResults(horizontal_pools * vertical_pools, 0);

	int offset = 0;
	for (int i = 0; i < vertical_pools; i++)
	{
		int offset = i * image_size.first * pool_size.second;
		for (int j = 0; j < horizontal_pools; j++)
		{
			poolResults[horizontal_pools*i + j] = maxPool(image, offset);
			offset += pool_size.first;
		}
	}

	return std::make_unique<ModelOutputDataVector>(poolResults);
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
