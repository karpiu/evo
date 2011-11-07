#include <iostream>
#include "random.hpp"

int main(int argc, char* argv[])
{
  init_random();
  std::cout << uniform_random() << std::endl;
  return 0;
}
