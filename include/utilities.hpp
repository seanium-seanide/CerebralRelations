#pragma once

#include <string>
#include <istream>

namespace utilities
{

auto lstrip(std::string str) -> std::string;
auto rstrip(std::string str) -> std::string;
auto strip(std::string str) -> std::string;
auto readText(std::istream& is) -> std::string;
auto readTextFile(const std::string& filename) -> std::string;

} // namespace utilities
