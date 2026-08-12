#include "CerebralRelations.hpp"

#include <vector>
#include <stack>
#include <ranges>
#include <istream>
#include <cstring>
#include "utilities.hpp"

using namespace std::string_literals;


CerebralRelations::CerebralRelations()
{
  reset();
}


auto CerebralRelations::loadScript(std::string_view script) -> void
{
  m_script = script;
  auto stack = std::stack(std::vector<int>());

  for (auto const [i, c]: std::views::enumerate(script))
  {
    switch (c)
    {
      case '[':
      {
        stack.push(i);
        break;
      }

      case ']':
      {
        auto index = stack.top();
        stack.pop();

        m_braceMap[index] = i;
        m_braceMap[i] = index;

        break;
      }

      default:
      {
        break;
      }
    }
  }
}


auto CerebralRelations::loadFile(const std::string& filename) -> void
{
  auto script = utilities::readTextFile(filename);
  loadScript(script);
}


auto CerebralRelations::dumpScript() -> std::string
{
  return m_script;
}


auto CerebralRelations::run(std::ostream& os, std::istream& is) -> void
{
  for (size_type instructionPointer = 0; instructionPointer < m_script.size(); ++instructionPointer)
  {
    auto instruction = m_script[instructionPointer];

    switch (instruction)
    {
      case '>':
      {
        if (m_dataPointer == m_data.size() - 1)
        {
          throw std::out_of_range("Attempted to step from tape at right side");
        }
        ++m_dataPointer;

        break;
      }

      case '<':
      {
        if (m_dataPointer == 0)
        {
          throw std::out_of_range("Attempted to step from tape at left side");
        }
        --m_dataPointer;

        break;
      }

      case '+':
      {
        ++m_data[m_dataPointer];

        break;
      }

      case '-':
      {
        --m_data[m_dataPointer];

        break;
      }

      case '.':
      {
        os << static_cast<char>(m_data[m_dataPointer]);

        break;
      }

      case ',':
      {
        int value{};
        is >> value;
        m_data[m_dataPointer] = value;

        break;
      }

      case '[':
      {
        if (m_data[m_dataPointer] == 0)
        {
          instructionPointer = m_braceMap[instructionPointer];
        }
        break;
      }

      case ']':
      {
        if (m_data[m_dataPointer] != 0)
        {
          instructionPointer = m_braceMap[instructionPointer];
        }

        break;
      }

      default:
      {
        break;
      }
    }
  }
}


auto CerebralRelations::reset() -> void
{
  m_dataPointer = 0;
  std::memset(m_data.data(), static_cast<size_type>(0), tape_size);
}
