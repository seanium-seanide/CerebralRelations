#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "utilities.hpp"

using namespace std::string_literals;


TEST_CASE("Stripping whitespace from the start of a string")
{
  auto string = "abc"s;


  SECTION("Stripping does not affect a string with no leading whitespace")
  {
    auto result = utilities::lstrip(string);

    REQUIRE(result == string);
  }

  SECTION("Each indivudual kind of whitespace is stripped from the beginning of a string")
  {
    auto leadingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");

    auto result = utilities::lstrip(leadingChar + string);

    REQUIRE(result == string);
  }

  SECTION("A sequence of leading whitespace is stripped from a string")
  {
    auto leadingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");

    auto result = utilities::lstrip(leadingWhitespace + string);

    REQUIRE(result == string);
  }
}


TEST_CASE("Stripping whitespace from the end of a string")
{
  auto string = "abc"s;


  SECTION("Stripping does not affect a string with no trailing whitespace")
  {
    auto result = utilities::rstrip(string);

    REQUIRE(result == string);
  }
  
  SECTION("Each individual kind of whitespace is stripped from the end of a string")
  {
    auto trailingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");

    auto result = utilities::rstrip(string + trailingChar);

    REQUIRE(result == string);
  }

  SECTION("A sequence of trailing whitespace is stripped from a string")
  {
    auto trailingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");

    auto result = utilities::rstrip(string + trailingWhitespace);

    REQUIRE(result == string);
  }
}


TEST_CASE("Stripping whitespace from the start and end of a string")
{
  auto string = "abc"s;


  SECTION("Stripping does not affect a string with no leading whitespace")
  {
    auto result = utilities::strip(string);

    REQUIRE(result == string);
  }

  SECTION("Each indivudual kind of whitespace is stripped from the beginning and end of a string")
  {
    auto leadingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");
    auto trailingChar = GENERATE("", " ", "\f", "\n", "\r", "\t", "\v");

    auto result = utilities::strip(leadingChar + string + trailingChar);

    REQUIRE(result == string);
  }

  SECTION("Sequences of leading and trailing whitespace are stripped from a string")
  {
    auto leadingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");
    auto trailingWhitespace = GENERATE("", "    ", "\f\t\n\r\t\v");

    auto result = utilities::strip(leadingWhitespace + string + trailingWhitespace);

    REQUIRE(result == string);
  }
}


TEST_CASE("Reading text from an input stream")
{
  SECTION("Reading from an empty stream returns the empty string")
  {
    auto iss = std::istringstream();
    auto input = ""s;
    iss.str(input);

    auto result = utilities::readText(iss);

    REQUIRE(result == input);
  }

  SECTION("Reading from a text stream returns the text in the stream")
  {
    auto iss = std::istringstream();
    auto input = std::string(
      "This is the first line\n"
      "This is the second line line\n"
      "This is the penultimate line line\n"
      "\n"
      "This is the final line\n"
    );
    iss.str(input);

    auto result = utilities::readText(iss);

    REQUIRE(result == input);
  }
}
