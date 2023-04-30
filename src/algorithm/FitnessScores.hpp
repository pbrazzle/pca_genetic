#ifndef FITNESS_SCORES
#define FITNESS_SCORES
#include <vector>

namespace PCAGenetic
{
	class FitnessScores
	{
	private:
		std::vector<double> scores;

	public:
		FitnessScores() = default;

		double& operator[](const size_t& i);
		double at(const size_t& i) const;

		std::vector<size_t> getSortedIndices() const;
		void sort();

		void replace(const std::vector<double>& newScores);

		void append(const double& score);

		void clear();

		double best() const;
		double avg() const;

		const std::vector<double>& asVector() const;
	};
}

#endif
