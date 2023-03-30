/*#include "GeneticModel.test.hpp"


int main()
{
	LinearModelTests tests;
	tests.runTests();
	
	return 0;
}*/

#include "LinearGeneticModel.hpp"
#include "GeneticModel.test.hpp"

using namespace GeneticModels;

class LinearModelTests : public GeneticModelTests
{
	public:
		std::unique_ptr<GeneticModel> createModel()
		{
			return std::unique_ptr<GeneticModel>(new LinearGeneticModel(3));
		}
		
		//TODO Add evaluation test
};

std::unique_ptr<GeneticModelTests> getTestClass() { return std::unique_ptr<GeneticModelTests>(new LinearModelTests()); }

TEST_CASE("Blank Test", "[LinearGeneticModel]")
{
	REQUIRE(true);
}