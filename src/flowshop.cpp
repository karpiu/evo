#include "flowshop.hpp"

// initiate flowshop-state-machine with 'm' machines that are idle.
void flowshop::initialize(int n, int m)
{
  size = m;
  idle = true;
  time = 0;

  C = new int[size];
  C_prev = new int[size];

  for(int i = 0; i < m; ++i)
    machs.push_back(machine(n));
}

// dynamic algorithm computing Cmax
int flowshop::cmax(const std::vector<int> &v)
{
  unsigned int i,j;

  memset( C_prev, 0, size*sizeof(int) ); // init with zeros

  for( i=0; i<v.size(); i++ )
  {
    C[0] = C_prev[0] + machs[0].time_table[v[i]];
    for( j=1; j<size; j++ )
      C[j] = std::max(C[j-1], C_prev[j]) + machs[j].time_table[v[i]];
    std::swap( C, C_prev ); // swap pointers
  }

  return C_prev[size-1];
}

flowshop::~flowshop()
{
  delete [] C;
  delete [] C_prev;
}

std::ostream& operator << (std::ostream& os, const flowshop& f)
{
  os << "[ ";
  for(auto i = f.machs.begin(); i != f.machs.end(); ++i)
    os << "("<< i->job << "/" << i->countdown << ") ";
  os << "]";
  return os;
}
