#include "CerebralRelations.hpp"


int main()
{
  auto interpreter = CerebralRelations();
  
  interpreter.loadFile("tests/assets/scripts/repeat.bf");
  interpreter.run();

  return 0;
}
