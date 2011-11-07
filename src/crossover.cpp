#include "crossover.hpp"

std::pair<permutation, permutation> crossover::partial_matched(permutation& p1, permutation& p2)
{
  assert(p1.N() == p2.N());

  std::vector<int> result1(p1.P().begin(), p1.P().end());
  std::vector<int> result2(p2.P().begin(), p2.P().end());

  
  return std::make_pair(p1, p2);
}
