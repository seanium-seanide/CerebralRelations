#pragma once

#include <string>
#include <array>
#include <iostream>
#include <ostream>
#include <cstdint>


class CerebralRelations
{
  static constexpr std::size_t TAPE_SIZE = 30000;

public:
  CerebralRelations();

  void loadScript(const std::string& script);
  std::string dumpScript();
  void run(std::ostream& os = std::cout);

private:
  std::string m_script;
  std::array<uint8_t, TAPE_SIZE> m_data;
};
