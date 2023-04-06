#include "GeneticAlgorithm.hpp"
#include "GeneticAlgorithmFactory.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace PCAGenetic;
using namespace JSON_IO;

TEST_CASE("GeneticAlgorithm", "[GeneticAlgorithm]")
{
    GeneticAlgorithm alg = makeBasicAlgorithm();

    SECTION("Serializable")
    {
        JSONObject obj = alg.toJSON();

        REQUIRE(obj);

        //REQUIRE numerical parameters are serialized
        REQUIRE(obj["generationSize"]);
        REQUIRE(obj["offsetSize"]);
        REQUIRE(obj["mutationSize"]);
        REQUIRE(obj["mutationChance"]);
        REQUIRE(obj["elitism"]);

        //REQUIRE strategies are serialized
        REQUIRE(obj["FitnessCalculator"]);
        REQUIRE(obj["ParentSelector"]);
        REQUIRE(obj["ParentCombiner"]);
    }
}