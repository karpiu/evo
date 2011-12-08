#include <iostream>
#include <fstream>
#include <vector>
#include "permutation.hpp"
#include "flowshop.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    cout << "usage: ./eval_perm.e [flowshop_instance_file]\n";
    return 1;
  }

  ifstream costs(argv[1]);
  flowshop f;
  int M, N;
  costs >> N;
  costs >> M;

  f.initialize(N,M);

  for(int x = 0; x < M; ++x)
    for(int y = 0; y < N; ++y)
      costs >> f[x][y];
  
  vector<int> v;
  int perm_el;
  while(cin >> perm_el)
    v.push_back(perm_el - 1);

  permutation p(v); // for assert(is_permutation)
  cout << f.cmax(p.P()) << endl;
  
  return 0;
}
