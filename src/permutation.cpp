#include "permutation.hpp"

permutation::permutation(const int N, const type t)
{
  perm.reserve(N);

  switch(t)
  {
    case random:
      break;
    case identity:
      break;
  }
}

bool permutation::valid_permutation() const
{
  return true;
}
