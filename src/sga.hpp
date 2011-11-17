#pragma once

#include <vector>
#include "permutation.hpp"

struct specimen
{
  permutation perm;
  float eval, adapt; // evaluation and adaptation value
};

typedef std::vector<specimen> population;

class sga
{
public:

  // create initial population
  population (*initial_population)();

  // compute adaptation function for every specimen in population
  void (*adaptation)(population& p);

  // compute elavuation function for every specimen in population
  void (*evaluate)(population& p);

  bool (*termination)(const population& p);
  void (*mutation)(population& p);
  void (*crossover)(population& p);
  void (*replacement)(population& p);
  void (*raport)(population& p);

  void run();
};
