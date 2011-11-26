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
  crossover::type crossover_type;
  bool debug;
  bool raport_population;
  bool raport_best;
};

void solve_flowshop(config& cfg);
