#include "utilities.hpp"

#include <algorithm>
#include <ranges>
#include <cctype>


namespace
{
  auto whitespacePredicate
    = [](const char c) 
      {
        return std::isspace(c); 
      };
} // anonymous namespace


namespace utilities
{

std::string lstrip(std::string str)
{
    auto it = std::ranges::find_if_not(str, ::whitespacePredicate);

    str.erase(str.begin(), it);
    return str;
}


std::string rstrip(std::string str)
{
    auto it = std::ranges::find_if_not(str | std::views::reverse, ::whitespacePredicate);

    str.erase(it.base(), str.end());
    return str;
}


std::string strip(std::string str)
{
  return rstrip(lstrip(str));
}

} // namespace utilities
