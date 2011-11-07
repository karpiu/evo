#pragma once

#include <vector>
#include <algorithm>
#include <cassert>

#include "random.hpp"

/*
 * Representation of permutation:
 * * vector of integers
 * * elements of vector are in <0...N-1>
 * * every element of vector is distinct
 *
 * example:
 * * vector [ 1, 0, 3, 2 ]
 * * represents algebraic permutation:
 * * / 1 2 3 4 \
 * * \ 2 1 4 3 /
 */

class permutation
{
private:
  std::vector<int> perm;
  bool valid_permutation() const;
public:
  enum type
    {
      random,
      identity
    };
  permutation(const int N, const type t = identity);
  int length() const { return perm.size(); }
};
