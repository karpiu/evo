#include "mutation.hpp"

void mutation::random_transposition(permutation& p)
{
  const int a = rand() % p.N();
  const int b = rand() % p.N();
  p.transpose(a, b);
}
