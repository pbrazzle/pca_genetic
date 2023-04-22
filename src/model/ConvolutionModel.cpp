#include "ConvolutionModel.hpp"
#include "ModelOutputDataVector.hpp"

#include <stdexcept>

using GeneticModels::GeneticModel;
using GeneticModels::ModelOutputData;
using GeneticModels::ConvolutionModel;

ConvolutionModel::ConvolutionModel(int iw, int ih, int kw, int kh)
	: image_width(iw), image_height(ih), kernel_width(kw), kernel_height(kh), kernel_weights(kw*kh)
{
}

ConvolutionModel::ConvolutionModel(int iw, int ih, int kw, int kh, std::vector<double> weights)
	: image_width(iw), image_height(ih), kernel_width(kw), kernel_height(kh), kernel_weights(weights)
{
}

std::unique_ptr<GeneticModel> ConvolutionModel::clone() const
{
	return std::make_unique<ConvolutionModel>(image_width, image_height, kernel_width, kernel_height, kernel_weights);
}

std::unique_ptr<ModelOutputData> ConvolutionModel::evaluate(ModelInputData& input)
{
	int output_width = image_width - kernel_width + 1;
	int output_height = image_height - kernel_height + 1;

	std::vector<double> inputData = input.getData();
	if (inputData.size() != (image_width * image_height)) throw std::invalid_argument("Incorrect input image size");

	std::vector<double> output(output_width*output_height, 0.0);
	for (int i = kernel_height/2; i < image_height - kernel_height/2; i++)
	{
		for (int j = kernel_width/2; j < image_width - kernel_width/2; j++)
		{
			double result = 0.0;
			for (int i_k = -kernel_height/2; i_k <= kernel_height/2; i_k++)
			{
				for (int j_k = -kernel_width/2; j_k <= kernel_width/2; j_k++)
				{
					result += inputData[(i+i_k)*image_width + j+j_k] * kernel_weights[(i_k+kernel_height/2) * kernel_width + j_k+kernel_width/2];
				}
			}
			output[output_width*(i-kernel_height/2) + (j-kernel_width/2)] = result;
		}
	}
	return std::make_unique<ModelOutputDataVector>(output);
}

std::vector<double> ConvolutionModel::getParameters() const
{
	return kernel_weights;
}

void ConvolutionModel::setParameters(std::vector<double> weights)
{
	if (weights.size() != kernel_width * kernel_height) throw std::invalid_argument("Incorrect number of weights");
	kernel_weights = weights;
}

int ConvolutionModel::getInputDataLength() const
{
	return image_width*image_height;
}

int ConvolutionModel::getOutputDataLength() const
{
	int output_width = image_width - kernel_width + 1;
	int output_height = image_height - kernel_height + 1;
	return output_width*output_height;
}

JSON_IO::JSONObject ConvolutionModel::toJSON() const
{
	JSONObject obj;

	obj.addString("typename", "ConvolutionModel");

	JSONObject dataObj;
	dataObj.addInt("image_width", image_width);
	dataObj.addInt("image_height", image_height);
	dataObj.addInt("kernel_width", kernel_width);
	dataObj.addInt("kernel_height", kernel_height);

	std::vector<JSONObject> weightArr;
	for (auto w : kernel_weights) weightArr.push_back(JSONObject(w));
	dataObj.addArray("weights", weightArr);

	obj.addObject("data", dataObj);

	return obj;
}

void ConvolutionModel::fromJSON(const JSONObject& obj)
{
	image_width = obj["image_width"].asInt();
	image_height = obj["image_height"].asInt();
	kernel_width = obj["kernel_width"].asInt();
	kernel_height = obj["kernel_height"].asInt();

	kernel_weights.clear();
	for (auto weightObj : obj["weights"].asArray())
	{
		kernel_weights.push_back(weightObj.asFloat());
	}
}
