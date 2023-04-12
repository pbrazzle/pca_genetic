#include "ModelInputImage.hpp"
#include "../external/CImg.h"

using namespace cimg_library;

void GeneticModels::ModelInputImage::readImage()
{
	CImg<double> image(filename.c_str());
	const int imgWidth = image.width();
	const int imgHeight = image.height();
	const int channels = image.spectrum();

	data.clear();
	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++)
		{
			double sum = 0.0;
			for (int k = 0; k < channels; k++) sum += image(j, i, 0, k);
			data.push_back(sum / channels);
		}
	}
}

GeneticModels::ModelInputImage::ModelInputImage(std::string f) : filename(f)
{
	readImage();
}

JSON_IO::JSONObject GeneticModels::ModelInputImage::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "ModelInputImage");

	JSONObject dataObj;
	dataObj.addString("filename", filename);
	obj.addObject("data", dataObj);

	return obj;
}

void GeneticModels::ModelInputImage::fromJSON(const JSONObject& obj)
{
	filename = obj["filename"].asString();
	readImage();
}

std::unique_ptr<GeneticModels::ModelInputData> GeneticModels::ModelInputImage::clone() const
{
	return std::make_unique<ModelInputImage>(filename);
}

std::vector<double> GeneticModels::ModelInputImage::getData()
{
	return data;
}
