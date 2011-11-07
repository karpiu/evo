#pragma once

#include <algorithm>

#include "permutation.hpp"

namespace crossover
{
  std::pair<permutation, permutation> partial_matched(permutation& p1, permutation& p2, int r, int s);

  std::pair<permutation, permutation> random_pmx(permutation& p1, permutation& p2);
}
