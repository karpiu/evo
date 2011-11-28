#include "mutation.hpp"

void mutation::random_transposition(permutation& p)
{
  const int a = randid() % p.N();
  const int b = randid() % p.N();
  p.transpose(a, b);
}
