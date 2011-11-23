
#include "flowshop.hpp"

// initiate flowshop-state-machine with 'm' machines that are idle.
flowshop::flowshop(int m)
{
  while(m--)
  {
    machine mach;
    mach.job = 0;
    mach.is_working = false;
    mach.countdown = 0;
    machs.push_back(mach);  
  }
  time = 0;
}
