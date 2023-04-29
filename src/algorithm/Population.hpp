#ifndef POPULATION
#define POPULATION

#include <vector>
#include <memory>
#include <iterator>

#include "GeneticTypes.hpp"
#include "model/GeneticModel.hpp"

namespace PCAGenetic
{
	using namespace GeneticModels;
	class Population
	{

	private:
		std::vector<std::unique_ptr<GeneticModel>> members;

		void copyPop(const Population& rhs);

	public:
		Population() = default;
		Population(const size_t& size, const GeneticModel& templateModel, const double offsetSize);
		Population(const Population& rhs);

		Population& operator=(const Population& rhs);

		GeneticModel& operator[](const size_t& i);
		const GeneticModel& at(const size_t& i) const;
		const GeneticModel& back() const;

		std::vector<std::unique_ptr<GeneticModel>>::iterator begin();
		std::vector<std::unique_ptr<GeneticModel>>::iterator end();

		size_t size() const;

		void replace(const std::vector<std::unique_ptr<GeneticModel>>&);
		void replace(const std::vector<ModelHandle>&);

		void reorder(const std::vector<size_t> indices);

		void append(const std::unique_ptr<GeneticModel>&);
		void append(const ModelHandle&);
		void append(const std::vector<std::unique_ptr<GeneticModel>>&);
		void append(const std::vector<ModelHandle>&);

		void cullWithElitism(const double& elitism);

		std::vector<ModelHandle> asHandleVector() const;
	};
}

#endif
