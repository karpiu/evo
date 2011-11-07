#include "permutation.hpp"

permutation::permutation(const int N, const type t)
{
  perm.reserve(N);

  switch(t)
  {
    case random:
      gen_random_perm();
      break;
    case identity:
      gen_identity_perm();
      break;
  }
}

void permutation::gen_random_perm()
{
  for(int i = 0; i < length(); ++i)
    perm.push_back(i);
  for(int i = 0; i < length(); ++i)
    std::swap(perm[i], perm[rand() % (i + 1)]);
}

void permutation::gen_identity_perm()
{
  for(int i = 0; i < length(); ++i)
    perm.push_back(i);
}

bool permutation::valid_permutation() const
{
  return true;
}
