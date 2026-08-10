#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <sstream>
#include <stdexcept>
#include "CerebralRelations.hpp"

using namespace std::string_literals;


TEST_CASE("The interpreter can read a script", "[cerebral]")
{
  auto interpreter = CerebralRelations();

  auto script = GENERATE(
      ",>,[<.>-]"s
      , "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s
  );
  interpreter.loadScript(script);

  REQUIRE(script == interpreter.dumpScript());
}


TEST_CASE("The interpreter can print characters", "[cerebral]")
{
  auto interpreter = CerebralRelations();

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


TEST_CASE("The interpreter can write and print characters in sequential cells from right to left", "[cerebral]")
{
  auto interpreter = CerebralRelations();

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


TEST_CASE("The interpreter can write and print characters in sequential cells from left to right", "[cerebral]")
{
  auto interpreter = CerebralRelations();

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


TEST_CASE("The interpreter cannot run off the tape from the left", "[cerebral]")
{
  auto interpreter = CerebralRelations();

  interpreter.loadScript(">");
  REQUIRE_NOTHROW(interpreter.run());

  interpreter.reset();
  interpreter.loadScript("<");

  REQUIRE_THROWS_AS(interpreter.run(), std::runtime_error);
  REQUIRE_THROWS_WITH(interpreter.run(), Catch::Matchers::ContainsSubstring("left"));
}


TEST_CASE("The interpreter cannot run off the tape from the right", "[cerebral]")
{
  auto interpreter = CerebralRelations();

  interpreter.loadScript(std::string(CerebralRelations::tape_size -1, '>'));
  REQUIRE_NOTHROW(interpreter.run());

  interpreter.reset();
  interpreter.loadScript(std::string(CerebralRelations::tape_size, '>'));
  REQUIRE_THROWS_AS(interpreter.run(), std::runtime_error);
  REQUIRE_THROWS_WITH(interpreter.run(), Catch::Matchers::ContainsSubstring("right"));
}


TEST_CASE("The interpreter can perform subtraction", "[cerebral]")
{
  auto interpreter = CerebralRelations();

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
