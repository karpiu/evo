#pragma once

#include <vector>
#include "permutation.hpp"

typedef std::vector<permutation> population;

class sga
{
public:
  population (*initial_population)();
  bool (*termination)(const population& p);
  void (*mutation)(population& p);
  void (*crossover)(population& p);
  void (*replacement)(population& p);
  void (*raport)(population& p);

  void run();
};
