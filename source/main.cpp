#include "CerebralRelations.hpp"


int main()
{
  auto interpreter = CerebralRelations();
  
  interpreter.loadScript("++++--.");
  interpreter.run();

  return 0;
}
