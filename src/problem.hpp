#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

#include "statistics.hpp"
#include "random.hpp"
#include "sga.hpp"
#include "mutation.hpp"
#include "crossover.hpp"
#include "flowshop.hpp"

struct config
{
  enum report
    {
      none, best, avg
    };
  crossover::type crossover_type;
  bool debug;
  bool report_population;
  bool report_best;
  bool smart_termination;
  int max_iter;
  int optimum;
  bool report_var;
  report report_every;
};

void solve_flowshop(config& cfg);
