#include "CerebralRelations.hpp"

#include <cstring>
#include <fmt/core.h>

using namespace std::string_literals;


CerebralRelations::CerebralRelations()
{
  reset();
}


void CerebralRelations::loadScript(std::string_view script)
{
  m_script = script;
}


std::string CerebralRelations::dumpScript()
{
  return m_script;
}


void CerebralRelations::run(std::ostream& os, std::istream& is)
{
  auto dataPointer = static_cast<size_type>(0);

  for (size_type instructionPointer = 0; instructionPointer < m_script.size(); ++instructionPointer)
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
        if (m_data[dataPointer] == 255)
        {
          throw std::runtime_error("Attempted to imcrement data out of range");
        }

        ++m_data[dataPointer];
        break;
      }

      case '-':
      {
        if (m_data[dataPointer] == 0)
        {
          throw std::runtime_error("Attempted to decrement data out of range");
        }
        --m_data[dataPointer];
        break;
      }

      case '.':
      {
        os << static_cast<char>(m_data[dataPointer]);
        break;
      }

      case ',':
      {
        int value{};
        is >> value;
        m_data[dataPointer] = value;
      }

      default:
      {
        break;
      }
    }
  }
}


void CerebralRelations::reset()
{
  std::memset(m_data.data(), static_cast<size_type>(0), tape_size);
}
