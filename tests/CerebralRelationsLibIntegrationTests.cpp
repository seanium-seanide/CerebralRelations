#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <sstream>
#include "utilities.hpp"
#include "CerebralRelations.hpp"

using namespace std::string_literals;


TEST_CASE("Brainfuck interpreter integration tests")
{
  auto interpreter = CerebralRelations();


  SECTION("Hello World")
  {
    REQUIRE_NOTHROW(interpreter.loadFile("assets/scripts/hello_world_verbose.bf"));

    auto oss = std::ostringstream();
    interpreter.run(oss);
    auto result = oss.str();
    auto expectedResult = "Hello World!\n"s;

    REQUIRE(result == expectedResult);
  }

  SECTION("Beer")
  {
    REQUIRE_NOTHROW(interpreter.loadFile("assets/scripts/beer.bf"));

    auto oss = std::ostringstream();
    interpreter.run(oss);
    auto result = oss.str();
    auto expectedResult = utilities::readTextFile("assets/outputs/beer.out");

    REQUIRE(result == expectedResult);
  }

  SECTION("Fibonacci")
  {
    REQUIRE_NOTHROW(interpreter.loadFile("assets/scripts/fibonacci.bf"));

    auto oss = std::ostringstream();
    interpreter.run(oss);
    auto result = oss.str();
    auto expectedResult = "1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89";

    REQUIRE(result == expectedResult);
  }

  SECTION("Cell Size")
  {
    REQUIRE_NOTHROW(interpreter.loadFile("assets/scripts/cell_size.bf"));

    auto oss = std::ostringstream();
    interpreter.run(oss);
    auto result = oss.str();
    auto expectedResult = "8 bit cells\n";

    REQUIRE(result == expectedResult);
  }

  SECTION("Repeat")
  {
    REQUIRE_NOTHROW(interpreter.loadFile("assets/scripts/repeat.bf"));

    auto oss = std::ostringstream();
    auto iss = std::istringstream();
    iss.str("65 10");
    interpreter.run(oss, iss);
    auto result = oss.str();
    auto expectedResult = std::string(10, 'A');

    REQUIRE(result == expectedResult);
  }
}
