#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

#include "random.hpp"
#include "sga.hpp"
#include "mutation.hpp"
#include "crossover.hpp"
#include "flowshop.hpp"

struct config
{
  enum raport
    {
      none, best, avg
    };
  crossover::type crossover_type;
  bool debug;
  bool raport_population;
  bool raport_best;
  int max_iter;
  raport raport_every;
};

void solve_flowshop(config& cfg);
