#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <sstream>
#include "CerebralRelations.hpp"

using namespace std::string_literals;


TEST_CASE("Brainfuck interpreter end-to-end tests", "[integration]")
{
  auto interpreter = CerebralRelations();


  SECTION("Hello World!")
  {
    interpreter.loadFile("assets/hello_world_verbose.bf");
    auto oss = std::ostringstream();
    interpreter.run(oss);

    REQUIRE(oss.str() == "Hello World!");
  }
}
