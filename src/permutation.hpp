#pragma once

#include <vector>
#include <cassert>

#include "random.hpp"

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
};
