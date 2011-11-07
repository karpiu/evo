#include "sga.hpp"

void sga::run()
{
  population p = initial_population();
  while(!termination(p))
  {
    crossover(p);
    mutation(p);
    replacement(p);
  }
  raport(p);
}
