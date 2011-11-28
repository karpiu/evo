#pragma once

#ifdef WIN32
  #include <process.h>
#else
  #include <unistd.h>
#endif


#include <cstdlib>
#include <ctime>

void init_random();
float uniform_random();
int randid();

