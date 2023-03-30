/*#include "GeneticModel.test.hpp"
#include "DownSamplingModel.hpp"

using namespace GeneticModels;

class DownSamplingModelTests : public GeneticModelTests
{
	public:
		std::unique_ptr<GeneticModel> createModel()
		{
			return std::unique_ptr<GeneticModel>(new DownSamplingModel());
		}
		
		//TODO Add evaluation test
};

int main()
{
	DownSamplingModelTests tests;
	tests.runTests();
	
	return 0;
}*/

#include <catch2/catch_test_macros.hpp>