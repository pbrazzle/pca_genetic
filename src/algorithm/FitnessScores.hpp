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
		[[nodiscard]] double at(const size_t& i) const;

		[[nodiscard]] std::vector<size_t> getSortedIndices() const;
		void sort();

		void replace(const std::vector<double>& newScores) noexcept;

		void append(const double& score) noexcept;

		void clear() noexcept;

		[[nodiscard]] double best() const noexcept;
		[[nodiscard]] double avg() const noexcept;

		[[nodiscard]] const std::vector<double>& asVector() const noexcept;
	};
}

#endif
