#include "algorithm/FitnessScores.hpp"

#include <algorithm>
#include <numeric>


double& PCAGenetic::FitnessScores::operator[](const size_t& i)
{
	return scores[i];
}

double PCAGenetic::FitnessScores::at(const size_t& i) const
{
	return scores.at(i);
}

std::vector<size_t> PCAGenetic::FitnessScores::getSortedIndices() const
{
	std::vector<size_t> sortedIndices(scores.size(), 0);
	std::iota(sortedIndices.begin(), sortedIndices.end(), 0);

	std::sort(sortedIndices.begin(), sortedIndices.end(),
		[&](size_t i1, size_t i2) { return scores[i1] < scores[i2]; });
	return sortedIndices;
}

void PCAGenetic::FitnessScores::sort()
{
	std::sort(scores.begin(), scores.end());
}

void PCAGenetic::FitnessScores::replace(const std::vector<double>& newScores) noexcept
{
	scores = newScores;
}

void PCAGenetic::FitnessScores::append(const double& score) noexcept
{
	scores.emplace_back(score);
}

void PCAGenetic::FitnessScores::clear() noexcept
{
	scores.clear();
}

double PCAGenetic::FitnessScores::best() const noexcept
{
	if (scores.empty()) return 0.0;
	return scores.back();
}

double PCAGenetic::FitnessScores::avg() const noexcept
{
	if (scores.empty()) return 0.0;
	return std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
}

const std::vector<double>& PCAGenetic::FitnessScores::asVector() const noexcept
{
	return scores;
}


