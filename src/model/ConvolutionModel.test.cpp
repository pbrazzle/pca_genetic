/*#include "GeneticModel.test.hpp"
#include "ConvolutionModel.hpp"

using namespace GeneticModels;

class ConvolutionModelTests : public GeneticModelTests
{
	public:
		std::unique_ptr<GeneticModel> createModel()
		{
			return std::unique_ptr<GeneticModel>(new ConvolutionModel());
		}
		
		//TODO Add evaluation test
};

int main()
{
	ConvolutionModelTests tests;
	tests.runTests();
	
	return 0;
}*/

#include <catch2/catch_test_macros.hpp>