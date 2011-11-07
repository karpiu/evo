#include "permutation.hpp"

permutation::permutation(const int N, const type t)
{
  perm.reserve(N);

  switch(t)
  {
    case random:
      for(int i = 0; i < N; ++i)
	perm.push_back(i);
      for(int i = 0; i < N; ++i)
	std::swap(perm[i], perm[rand() % (i + 1)]);
      break;
    case identity:
      for(int i = 0; i < N; ++i)
	perm.push_back(i);
      break;
  }
}

bool permutation::valid_permutation() const
{
  return true;
}
