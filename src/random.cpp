#include "random.hpp"

static float uniform_deviate(int seed)
{
  return seed * (1.0f / (RAND_MAX + 1.0f));
}

void init_random_based_on_time()
{
  srand(time(NULL));
}

void init_random(int seed)
{
  srand(seed);
}

float uniform_random()
{
  return uniform_deviate(randid());
}

int randid()
{
  #ifdef WIN32
    return rand()+_getpid();
  #else
    return rand()+getpid();
  #endif
}

