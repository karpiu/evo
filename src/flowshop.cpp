#include "flowshop.hpp"

flowshop::flowshop()
{
  size = 0;
  idle = true;
  time = 0;
}

// initiate flowshop-state-machine with 'm' machines that are idle.
flowshop::flowshop(int n, int m)
{
  size = m;
  
  machine* mach = 0;
  while(m--)
  {
    mach = new machine(n);  
    machs.push_back(*mach);
  }
  idle = true;
  time = 0;
}

flowshop::flowshop( const flowshop &f )
{  
  if(this != &f) {
    time = f.time;
    idle = f.idle;
    size = f.size;
    machs = std::vector<machine>(f.machs);
  }
}



void flowshop::update()
{
  time++;
  
  // count for non-working machines
  unsigned int not_working = 0;
  
  for(int i=size-1; i>=0; i--)
  {
    if(machs[i].is_working) 
    {
      if(machs[i].countdown == 0)
      {
        // if the job is done on this machine, we try to put it on the next machine
        if( i == (int)size-1 )
        {
          // if job on the last machine is finished we just flag this machine
          machs[i].is_working = false;
          machs[i].job = 0;
        } else if ( ! machs[i+1].is_working ) {
          // next machine is ready to take the new job
          machs[i+1].is_working = true;
          machs[i+1].job = machs[i].job;
          machs[i+1].countdown = machs[i+1].time_table[machs[i+1].job]; 
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


void flowshop::add_job(int job)
{
  machs[0].job = job;
  machs[0].is_working = true;
  machs[0].countdown = machs[0].time_table[job];
  
  if(idle)
    idle = false;
}

void flowshop::clear_flow()
{
  for(unsigned int i=0; i<size; i++) {
    machs[i].job = 0;
    machs[i].is_working = false;
    machs[i].countdown = 0;  
  }
  idle = true;
  time = 0;
}

// simulation start
void flowshop::run(std::queue<int> &q)
{  
  clear_flow();
   
  if(q.empty())
    return;  
  
  add_job(q.front()); 
  q.pop();
  
  while( !q.empty() || !is_done() ) {
    update();
    if( !q.empty() && is_ready() ) {
      add_job(q.front());
      q.pop();
    }
  }
}

// dynamic algorithm computing Cmax
int flowshop::cmax(const std::vector<int> &v)
{
  unsigned int i,j;
  int* C = new int[size];
  int* C_prev = new int[size];  
  
  memset( C_prev, 0, size*sizeof(int) ); // init with zeros

  for( i=0; i<v.size(); i++ )
  {
    C[0] = C_prev[0] + machs[0].time_table[v[i]];
    for( j=1; j<size; j++ )
      C[j] = std::max(C[j-1], C_prev[j]) + machs[j].time_table[v[i]];
    std::swap( C, C_prev ); // swap pointers 
  }
  delete [] C;
  delete [] C_prev;
  
  return C_prev[size-1];
}

std::ostream& operator << (std::ostream& os, const flowshop& f)
{
  os << "[ ";
  for(auto i = f.machs.begin(); i != f.machs.end(); ++i)
    os << "("<< i->job << "/" << i->countdown << ") ";
  os << "]";
  return os;
}
