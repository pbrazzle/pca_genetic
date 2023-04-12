#pragma once

#include "ModelInputData.hpp"

namespace GeneticModels
{
	class ModelInputImage : public ModelInputData
	{
	private:
		std::string filename;
		std::vector<double> data;

		void readImage();

	public:
		ModelInputImage() = default;
		ModelInputImage(std::string);

		JSONObject toJSON() const override;
		void fromJSON(const JSONObject& obj) override;
		std::unique_ptr<ModelInputData> clone() const override;
		std::vector<double> getData() override;
	};
}
