#include "ModelInputDataVector.hpp"
#include <memory>

using namespace GeneticModels;
using namespace JSON_IO;

ModelInputDataVector::ModelInputDataVector(std::vector<double> d) : data(d) { }

std::unique_ptr<ModelInputData> ModelInputDataVector::clone() const
{
	return std::unique_ptr<ModelInputData>(new ModelInputDataVector(data));
}

std::vector<double> ModelInputDataVector::getData() { return data; }

JSONObject ModelInputDataVector::toJSON() const
{
	JSONObject obj;
	obj.addString("typename", "ModelInputDataVector");
	
	std::vector<JSONObject> dataJSON;
	for (double d : data) dataJSON.push_back(JSONObject(d));
	obj.addArray("data", dataJSON);
	
	return obj;
}

void ModelInputDataVector::fromJSON(const JSONObject& obj)
{
	auto dataArr = obj.asArray();

	data.clear();
	for (auto dataObj : dataArr) data.push_back(dataObj.asFloat());
}
