#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <sstream>
#include <stdexcept>
#include "CerebralRelations.hpp"

using namespace std::string_literals;


TEST_CASE("Brainfuck interpreter tests", "[cerebral]")
{
  auto interpreter = CerebralRelations();


  SECTION("The interpreter can read a script")
  {
    auto script = GENERATE(
        ",>,[<.>-]"s
        , std::string(static_cast<int>('A'), '+') + "."
    );
    interpreter.loadScript(script);

    REQUIRE(script == interpreter.dumpScript());
  }

  SECTION("The interpreter can print characters")
  {
    auto [script, expectedResult] = GENERATE(
        std::pair(std::string(static_cast<int>('A'), '+') + ".", "A")
      , std::pair(std::string(static_cast<int>('B'), '+') + ".", "B")
      , std::pair(std::string(static_cast<int>('A'), '+') + "."s
                + std::string(static_cast<int>('G' - 'A'), '+') + ".", "AG")
    );
    interpreter.loadScript(script);
    auto oss = std::ostringstream();
    interpreter.run(oss);
    
    auto result = oss.str();
    REQUIRE(result == expectedResult);
  }

  SECTION("The interpreter can write and print characters in sequential cells from right to left")
  {
    auto [script, expectedResult] = GENERATE(
        std::pair(std::string(static_cast<int>('A'), '+') + ".>"
                + std::string(static_cast<int>('B'), '+') + ".", "AB")
      , std::pair(std::string(static_cast<int>('A'), '+') + ".>"s
                + std::string(static_cast<int>('B'), '+') + ".>"s
                + std::string(static_cast<int>('C'), '+') + ".", "ABC")
    );
    interpreter.loadScript(script);
    auto oss = std::ostringstream();
    interpreter.run(oss);
    
    auto result = oss.str();
    REQUIRE(result == expectedResult);
  }

  SECTION("The interpreter can write and print characters in sequential cells from left to right")
  {
    auto [script, expectedResult] = GENERATE(
        std::pair(">"s + std::string(static_cast<int>('A'), '+') + ".<"
                       + std::string(static_cast<int>('B'), '+') + ".", "AB")
    );
    interpreter.loadScript(script);
    auto oss = std::ostringstream();
    interpreter.run(oss);
    
    auto result = oss.str();
    REQUIRE(result == expectedResult);
  }

  SECTION("The interpreter cannot run off the tape from the left")
  {
    REQUIRE_NOTHROW(interpreter.run());

    interpreter.reset();
    interpreter.loadScript("<");

    REQUIRE_THROWS_AS(interpreter.run(), std::runtime_error);
    REQUIRE_THROWS_WITH(interpreter.run(), Catch::Matchers::ContainsSubstring("left"));
  }

  SECTION("The interpreter cannot run off the tape from the right")
  {
    interpreter.loadScript(std::string(CerebralRelations::tape_size -1, '>'));
    REQUIRE_NOTHROW(interpreter.run());

    interpreter.reset();
    interpreter.loadScript(std::string(CerebralRelations::tape_size, '>'));
    REQUIRE_THROWS_AS(interpreter.run(), std::runtime_error);
    REQUIRE_THROWS_WITH(interpreter.run(), Catch::Matchers::ContainsSubstring("right"));
  }

  SECTION("The interpreter can perform subtraction")
  {
    auto [script, expectedResult] = GENERATE(
        std::pair(std::string(static_cast<int>('D'), '+') + "."s
                + std::string(static_cast<int>('D' - 'A'), '-') + ".", "DA")
      , std::pair(std::string(static_cast<int>('Z'), '+') + "."s
                + std::string(static_cast<int>('Z' - 'L'), '-') + ".", "ZL")
      , std::pair(std::string(static_cast<int>('H'), '+') + "."s
                + std::string(static_cast<int>('H' - 'F'), '-') + ".", "HF")
    );
    interpreter.loadScript(script);
    auto oss = std::ostringstream();
    interpreter.run(oss);

    auto result = oss.str();
    REQUIRE(result == expectedResult);
  }

  SECTION("Cannot increment a cell beyond 255")
  {
    interpreter.loadScript(std::string(258, '+'));

    REQUIRE_THROWS_AS(interpreter.run(), std::runtime_error);
    REQUIRE_THROWS_WITH(interpreter.run(), Catch::Matchers::ContainsSubstring("out of range"));
  }

  SECTION("Cannot decrement a cell below 0")
  {
    interpreter.loadScript(std::string(1, '-'));

    REQUIRE_THROWS_AS(interpreter.run(), std::runtime_error);
    REQUIRE_THROWS_WITH(interpreter.run(), Catch::Matchers::ContainsSubstring("out of range"));
  }

  SECTION("Can read a value from stdin")
  {
    interpreter.loadScript(",.");
    auto oss = std::ostringstream();
    auto iss = std::istringstream();
    auto data = std::to_string(static_cast<int>('A'));
    iss.str(data);
    interpreter.run(oss, iss);

    REQUIRE(oss.str() == "A");
  }

  // Test list
  //
  // * [ ] State of interpreter is persisted between runs
  // * [ ] Can clear state of interpreter
  // * [ ] Can print items in a loop
}
