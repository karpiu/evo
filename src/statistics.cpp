#include "statistics.hpp"

int statistics::edit_distance( const permutation& a, const permutation& b )
{
  assert(a.N() == b.N());

  permutation p = a;
  permutation rp = p.reversed(); // move used instead of copying
  int res = 0;
  int n = p.N();
  
  for(int i=0; i<n; i++)
  {
    if(p[i] != b[i])
    {
      p.transpose(i, rp[b[i]]);
      res++;
    }
  }
  
  return res;
}

int statistics::var( const population& p, const int i )
{
  int n = p.size();
  int sum = 0;
  int e;
  
  for(int j=0; j<n; j++)
  {
    if(i == j)
      continue;
    e = edit_distance(p[i].perm,p[j].perm);
    sum += e*e;
  }

  return sum;
}

// returns index of the avarage specimen in population p
int statistics::avg_specimen( const population& p)
{
  int avg = 0;
  int v = var(p, avg);
  int v2;

  for(unsigned int i=1; i<p.size(); i++)
  {
    v2 = var(p, i);
    if( v2 < v )
    {
      avg = i;
      v = v2;
    }
  }
  return avg;
}

