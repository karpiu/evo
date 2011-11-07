#pragma once

#include <vector>
#include "permutation.hpp"

class sga
{
public:
  typedef std::vector<permutation> population;
  population (*initial_population)();
  bool (*termination_condition)(const population& p);
  void (*mutation)(population& p);
  void (*crossover)(population& p);
  void (*replacement)(population& p);

  void run();
};
