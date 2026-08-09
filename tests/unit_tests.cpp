#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <sstream>
#include "CerebralRelations.hpp"

using namespace std::string_literals;


TEST_CASE("The interpreter can read a script", "[cerebral_unit]")
{
  auto interpreter = CerebralRelations();

  auto script = GENERATE(
      ",>,[<.>-]"s
      , "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s
  );
  interpreter.loadScript(script);

  REQUIRE(script == interpreter.dumpScript());
}


TEST_CASE("The interpreter can print characters", "")
{
  auto interpreter = CerebralRelations();

  auto [script, expectedResult] = GENERATE(
      std::pair("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "A")
    , std::pair("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "B")
    , std::pair("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."s, "AB")
  );
  interpreter.loadScript(script);
  auto oss = std::ostringstream();
  interpreter.run(oss);
  
  auto result = oss.str();
  REQUIRE(result == expectedResult);
}
