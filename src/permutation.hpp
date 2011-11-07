#pragma once

#include <array>
#include <cassert>

// permutations of N elements
template<int N>
  class permutation
{
private:
  std::array<int, N> perm;
  bool valid_permutation() const;
public:
};
