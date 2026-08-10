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
        , "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s
    );
    interpreter.loadScript(script);

    REQUIRE(script == interpreter.dumpScript());
  }

  SECTION("The interpreter can print characters")
  {
    auto [script, expectedResult] = GENERATE(
        std::pair("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "A")
      , std::pair("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "B")
      , std::pair("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+.", "AB")
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
        std::pair("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."
                  ">++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "AB"),
        std::pair(" +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."
                  ">++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."
                  ">+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "ABC")
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
        std::pair(">+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."
                  "<++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "AB")
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
        std::pair(std::string(static_cast<int>('D'), '+') + "."s + std::string(static_cast<int>('D' - 'A'), '-') + ".", "DA")
      , std::pair(std::string(static_cast<int>('Z'), '+') + "."s + std::string(static_cast<int>('Z' - 'L'), '-') + ".", "ZL")
      , std::pair(std::string(static_cast<int>('H'), '+') + "."s + std::string(static_cast<int>('H' - 'F'), '-') + ".", "HF")
    );
    interpreter.loadScript(script);
    auto oss = std::ostringstream();
    interpreter.run(oss);

    auto result = oss.str();
    REQUIRE(result == expectedResult);
  }
}
