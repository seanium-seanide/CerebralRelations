#include <format>
#include <iostream>
#include <filesystem>
#include "CerebralRelations.hpp"


int main(int argc, char** argv)
{
  if (argc == 1) // REPL mode
  {
    auto interpreter = CerebralRelations();
    std::string line;

    std::cout << "CR> ";

    while (std::getline(std::cin, line))
    {
      interpreter.loadScript(line);

      std::cout << "out: ";
      interpreter.run();
      std::cout << "\n";

      std::cout << "\nCR> ";
    }

    std::cout << '\n';
  }
  else if (argc == 2) // Script mode
  {
    auto interpreter = CerebralRelations();

    interpreter.loadFile(argv[1]);
    interpreter.run();
  }
  else
  {
    std::cout << std::format(
        "Usage: {} [<script filename>]\n"
      , std::string(std::filesystem::path(argv[0]).filename())
    );
  }

  return 0;
}
