#include "CerebralRelations.hpp"

#include <cstring>
#include <fmt/core.h>

using namespace std::string_literals;


CerebralRelations::CerebralRelations()
{
  std::memset(m_data.data(), static_cast<std::size_t>(0), TAPE_SIZE);
}

void CerebralRelations::loadScript(const std::string& script)
{
  m_script = script;
}

std::string CerebralRelations::dumpScript()
{
  return m_script;
}

void CerebralRelations::run(std::ostream& os)
{
  auto dataPointer = static_cast<std::size_t>(0);

  for (std::size_t instructionPointer = 0; instructionPointer < m_script.size(); ++instructionPointer)
  {
    auto instruction = m_script[instructionPointer];

    switch (instruction)
    {
      case '>':
      {
        if (dataPointer == m_data.size() - 1)
        {
          throw std::runtime_error("Attempted to step from tape at right side");
        }

        ++dataPointer;
        break;
      }

      case '<':
      {
        if (dataPointer == 0)
        {
          throw std::runtime_error("Attempted to step from tape at left side");
        }

        --dataPointer;
        break;
      }

      case '+':
      {
        ++m_data[dataPointer];
        break;
      }

      case '.':
      {
        os << static_cast<char>(m_data[dataPointer]);
        break;
      }

      default:
      {
        break;
      }
    }
  }
}
