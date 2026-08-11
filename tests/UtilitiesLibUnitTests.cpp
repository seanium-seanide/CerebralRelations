#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "utilities.hpp"

using namespace std::string_literals;


TEST_CASE("UtilitiesLib unit tests")
{
  // lstrip()

  SECTION("lstrip does not affect a string with no leading whitespace")
  {
    auto string = "abc";

    auto result = utilities::lstrip(string);

    REQUIRE(result == string);
  }

  SECTION("lstrip strips each indivudual kind of whitespace from the beginning of a string")
  {
    auto leadingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");

    auto strippedString = "abc"s;
    auto result = utilities::lstrip(leadingChar + strippedString);

    REQUIRE(result == strippedString);
  }

  SECTION("lstrip strips a sequence of leading whitespace from a string")
  {
    auto leadingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");

    auto strippedString = "abc"s;
    auto result = utilities::lstrip(leadingWhitespace + strippedString);

    REQUIRE(result == strippedString);
  }

  // rstrip()

  SECTION("rstrip does not affect a string with no trailing whitespace")
  {
    auto string = "abc";

    auto result = utilities::rstrip(string);

    REQUIRE(result == string);
  }
  
  SECTION("rstrip strips each individual kind of whitespace from the end of a string")
  {
    auto trailingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");

    auto strippedString = "abc"s;
    auto result = utilities::rstrip(strippedString + trailingChar);

    REQUIRE(result == strippedString);
  }

  SECTION("rstrip strips a sequence of trailing whitespace from a string")
  {
    auto trailingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");

    auto strippedString = "abc"s;
    auto result = utilities::rstrip(strippedString + trailingWhitespace);

    REQUIRE(result == strippedString);
  }

  // strip()

  SECTION("strip does not affect a string with no leading whitespace")
  {
    auto string = "abc";

    auto result = utilities::strip(string);

    REQUIRE(result == string);
  }

  SECTION("strip strips each indivudual kind of whitespace from the beginning and end of a string")
  {
    auto leadingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");
    auto trailingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");

    auto strippedString = "abc"s;
    auto result = utilities::strip(leadingChar + strippedString + trailingChar);

    REQUIRE(result == strippedString);
  }

  SECTION("strip strips sequences of leading and trailing whitespace from a string")
  {
    auto leadingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");
    auto trailingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");

    auto strippedString = "abc"s;
    auto result = utilities::strip(leadingWhitespace + strippedString + trailingWhitespace);

    REQUIRE(result == strippedString);
  }
}
