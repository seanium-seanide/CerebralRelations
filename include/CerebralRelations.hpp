#pragma once

#include <string>
#include <string_view>
#include <array>
#include <iostream>
#include <ostream>
#include <cstdint>
#include <unordered_map>


class CerebralRelations
{
public:
  using size_type = std::size_t;
  using data_type = std::uint8_t;
  static constexpr size_type tape_size = 30000;

  CerebralRelations();

  auto loadScript(std::string_view script) -> void;
  auto loadFile(const std::string& filename) -> void;
  auto dumpScript() -> std::string;
  auto run(std::ostream& os = std::cout, std::istream& is = std::cin) -> void;
  auto reset() -> void;

private:
  std::string m_script;
  std::array<uint8_t, tape_size> m_data;
  size_type m_dataPointer{0};
  std::unordered_map<size_type, size_type> m_braceMap;
};
