#include "statistics.hpp"

int statistics::edit_distance( const permutation& a, const permutation& b )
{
  assert(a.N() == b.N());

  permutation p(a.P());
  int res = 0;
  int n = p.N();
  int* rp = new int[n];  

  // calculating reverse permutation of p1
  for(int i=0; i<n; i++)
    rp[p.P()[i]] = i;  
  
  for(int i=0; i<n; i++)
  {
    if(p.P()[i] != b.P()[i])
      p.transpose(i, rp[b.P()[i]]);
  }

  delete [] rp;
  
  return res;
}
