#include "CerebralRelations.hpp"


int main()
{
  auto interpreter = CerebralRelations();
  
  interpreter.loadFile("assets/hello_world_verbose.bf");
  interpreter.run();

  return 0;
}
