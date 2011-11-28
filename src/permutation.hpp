#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>

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
  void gen_random_perm();
  void gen_identity_perm();
public:
  enum type
    {
      random,
      identity
    };
  permutation(const int N, const type t = identity);
  permutation(const std::vector<int>&);
  permutation(const permutation& p);
  permutation(permutation&& p);
  permutation& operator=(const permutation& p);
  permutation() {} // unused, just for vector::resize shrinking purposes
  int N() const { return perm.size(); }
  const std::vector<int>& P() const { return perm; }
  int operator[](int n) const { return perm.at(n); }
  int elem_position(const int v) const;
  void transpose(const int a, const int b);
  friend std::ostream& operator << (std::ostream& os, const permutation& p);
  permutation reversed() const;
};
