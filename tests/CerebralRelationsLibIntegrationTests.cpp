#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <sstream>
#include "utilities.hpp"
#include "CerebralRelations.hpp"

using namespace std::string_literals;


TEST_CASE("Brainfuck interpreter integration tests")
{
  auto interpreter = CerebralRelations();


  SECTION("Hello World!")
  {
    REQUIRE_NOTHROW(interpreter.loadFile("assets/hello_world_verbose.bf"));
    auto oss = std::ostringstream();
    interpreter.run(oss);
    auto result = utilities::strip(oss.str());
    auto expectedResult = "Hello World!"s;

    REQUIRE(result == expectedResult);
  }
}
