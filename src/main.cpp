#include <iostream>
#include "random.hpp"
#include "permutation.hpp"

int main(int argc, char* argv[])
{
  init_random();
  permutation p(5, permutation::type::random);
  std::cout << p << std::endl;
  return 0;
}
