
#include "flowshop.hpp"

// initiate flowshop-state-machine with 'm' machines that are idle.
flowshop::flowshop(int m)
{
  size = m;

  while(m--)
  {
    machine mach;
    mach.job = 0;
    mach.is_working = false;
    mach.countdown = 0;
    machs.push_back(mach);  
  }
  idle = true;
  time = 0;
}

void flowshop::update()
{
  time++;
  
  // count for non-working machines
  int not_working = 0;

  for(int i=size-1; i>=0; i--)
  {
    if(machs[i].is_working) 
    {
      
      if(machs[i].countdown == 0)
      {
        // if the job is done on this machine, we try to put it on the next machine
        if( i == size-1 )
        {
          // if job on the last machine is finished we just flag this machine
          machs[i].is_working = false;
          machs[i].job = 0;
        } else if ( ! machs[i+1].is_working ) {
          // next machine is ready to take the new job
          machs[i+1].is_working = true;
          machs[i+1].job = machs[i].job;
          machs[i+1].countdown = ; ////////
          machs[i].is_working = false;
          machs[i].job = 0;
        }
        // ...otherwise the next machine is still running, so we do nothing
      } else {
        // advancing time to completion
        machs[i].countdown--;
      }
    } else {
      not_working++;
    }
  }
  
  // the evaluation of jobs is done when there is nothing in the flow
  if(not_working == size)
    idle = true;
}


bool flowshop::isDone()
{
  return idle;
}