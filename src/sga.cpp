#include "sga.hpp"

void sga::run()
{
  population p = initial_population();
	evaluate(p);  
	while(!termination(p))
  {
		adaptation(p);
    crossover(p);
    mutation(p);
    replacement(p);
		evaluate(p);
  }
  raport(p);
}
