#pragma once

#include <algorithm>

#include "permutation.hpp"

namespace crossover
{
  enum type
    {
      OX, CX, PMX
    };

  std::pair<permutation, permutation> random_crossover(type t, permutation& p1, permutation& p2);
  
  std::pair<permutation, permutation> pmx(permutation& p1, permutation& p2, int r, int s);

  std::pair<permutation, permutation> random_pmx(permutation& p1, permutation& p2);
  std::pair<permutation, permutation> ox(permutation& p1, permutation& p2, int r, int s);
  std::pair<permutation, permutation> random_ox(permutation& p1, permutation& p2);
  std::pair<permutation, permutation> cx(permutation& p1, permutation& p2, int r, int s);
  std::pair<permutation, permutation> random_cx(permutation& p1, permutation& p2);
}
