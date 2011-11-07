#include "crossover.hpp"

std::pair<permutation, permutation> crossover::partial_matched(permutation& p1, permutation& p2)
{
  assert(p1.N() == p2.N());
  return std::make_pair(p1, p2);
}
