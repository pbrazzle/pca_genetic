#include "Population.hpp"

using namespace PCAGenetic;

void Population::copyPop(const Population& rhs)
{
	replace(rhs.members);
}

Population::Population(const size_t& size, const GeneticModel& templateModel, const double offsetSize)
{
	members.reserve(size);
	for (int i = 0; i < size; i++) members.push_back(templateModel.copyWithOffset(offsetSize));
}

Population::Population(const Population& rhs)
{
	copyPop(rhs);
}

Population& Population::operator=(const Population& rhs)
{
	copyPop(rhs);
	return *this;
}

GeneticModel& Population::operator[](const size_t& i)
{
	return *members[i];
}

const GeneticModel& Population::at(const size_t& i) const
{
	return *members.at(i);
}

const GeneticModel& Population::back() const
{
	return *members.back();
}

std::vector<std::unique_ptr<GeneticModel>>::iterator Population::begin()
{
	return members.begin();
}

std::vector<std::unique_ptr<GeneticModel>>::iterator Population::end()
{
	return members.end();
}

size_t Population::size() const
{
	return members.size();
}

void Population::replace(const std::vector<std::unique_ptr<GeneticModel>>& newMembers)
{
	members.clear();
	for (int i = 0; i < newMembers.size(); i++) members.push_back(newMembers[i]->clone());
}

void Population::replace(const std::vector<ModelHandle>& newMembers)
{
	members.clear();
	for (int i = 0; i < newMembers.size(); i++) members.push_back(newMembers[i]->clone());
}

void Population::reorder(const std::vector<size_t> indices)
{
	std::vector<std::unique_ptr<GeneticModel>> reorderedPop;
	for (auto i : indices) reorderedPop.push_back(members[i]->clone());
	replace(reorderedPop);
}

void Population::append(const ModelHandle& model)
{
	members.emplace_back(model->clone());
}

void Population::cullWithElitism(const double& elitism)
{
	const auto numElite = static_cast<int>(members.size() * elitism);
	members.erase(members.begin(), members.end()-numElite);
}

std::vector<ModelHandle> Population::asHandleVector() const
{
	std::vector<ModelHandle> handles;
	for (int i = 0; i < members.size(); i++) handles.emplace_back(members[i]);
	return handles;
}
