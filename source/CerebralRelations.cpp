#include "CerebralRelations.hpp"

#include <vector>
#include <format>
#include <filesystem>
#include <stack>
#include <ranges>
#include <fstream>
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


void CerebralRelations::loadFile(const std::string& filename)
{
  auto file = std::ifstream(filename);
  if (!file)
  {
    throw std::runtime_error(std::format("Failed to open file {}. Current directory: {}", filename, std::string{std::filesystem::current_path()}));
  }

  auto script = std::string(std::istreambuf_iterator<char>{file}, {});

  loadScript(script);

  file.close();
}


std::string CerebralRelations::dumpScript()
{
  return m_script;
}


void CerebralRelations::run(std::ostream& os, std::istream& is)
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
          throw std::runtime_error("Attempted to step from tape at right side");
        }
        ++m_dataPointer;

        break;
      }

      case '<':
      {
        if (m_dataPointer == 0)
        {
          throw std::runtime_error("Attempted to step from tape at left side");
        }
        --m_dataPointer;

        break;
      }

      case '+':
      {
        if (m_data[m_dataPointer] == 255)
        {
          throw std::runtime_error("Attempted to imcrement data out of range");
        }
        ++m_data[m_dataPointer];

        break;
      }

      case '-':
      {
        if (m_data[m_dataPointer] == 0)
        {
          throw std::runtime_error("Attempted to decrement data out of range");
        }
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


void CerebralRelations::reset()
{
  m_dataPointer = 0;
  std::memset(m_data.data(), static_cast<size_type>(0), tape_size);
}
