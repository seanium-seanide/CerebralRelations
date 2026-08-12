#include "utilities.hpp"

#include <algorithm>
#include <format>
#include <fstream>
#include <filesystem>
#include <ranges>
#include <cctype>


namespace
{
auto whitespacePredicate = [](const char c) { return std::isspace(c); };
} // namespace


namespace utilities
{

auto lstrip(std::string str) -> std::string
{
    auto it = std::ranges::find_if_not(str, ::whitespacePredicate);

    str.erase(str.begin(), it);
    return str;
}


auto rstrip(std::string str) -> std::string
{
    auto it = std::ranges::find_if_not(str | std::views::reverse, ::whitespacePredicate);

    str.erase(it.base(), str.end());
    return str;
}


auto strip(std::string str) -> std::string
{
  return rstrip(lstrip(str));
}


auto readText(std::istream& is) -> std::string
{
  return {std::istreambuf_iterator<char>{is}, {}};
}


auto readTextFile(const std::string& filename) -> std::string
{
  auto file = std::ifstream(filename);
  if (!file)
  {
    throw std::runtime_error(
      std::format(
        "Failed to open file {}. Current directory: {}"
      , filename, std::string{std::filesystem::current_path()}
      )
    );
  }

  auto script = readText(file);

  file.close();

  return script;
}

} // namespace utilities
