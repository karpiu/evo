#include "sga.hpp"

void sga::run()
{
  population p = initial_population();
  evaluate(p);
  while(!termination(p))
  {
    adaptation(p);
    crossover(p);
    adaptation(p);
    mutation(p);
    adaptation(p);
    replacement(p);
    evaluate(p);
    raport(p);
  }
  raport_end(p);
}
