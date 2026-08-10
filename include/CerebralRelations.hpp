#pragma once

#include <string>
#include <array>
#include <iostream>
#include <ostream>
#include <cstdint>


class CerebralRelations
{
public:
  using size_type = std::size_t;
  static constexpr size_type tape_size = 30000;

  CerebralRelations();

  void loadScript(std::string_view script);
  std::string dumpScript();
  void run(std::ostream& os = std::cout);
  void reset();

private:
  std::string m_script;
  std::array<uint8_t, tape_size> m_data;
};
