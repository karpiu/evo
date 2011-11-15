#include "crossover.hpp"

std::pair<permutation, permutation> crossover::random_ox(permutation& p1, permutation& p2)
{
	assert(p1.N() == p2.N());
	
	int n = p1.N();
	int r = rand() % n;
  int s = rand() % n;
  if(r > s)
    std::swap(r, s);
	
	std::vector<int> result1(p1.P().begin(), p1.P().end());
	std::vector<int> tmp1(p1.P().begin(), p1.P().end()); // copy parent 1 for computing second child  
	std::vector<int> result2(p2.P().begin(), p2.P().end());
	
	std::vector<int>::iterator itr = result1.begin()+r;
	std::vector<int>::iterator its = result1.begin()+s+1;

	// computing first child
	int i = s+1;
	int res = s+1;
	while((i != s) || (res != r)){
		i %= n;
		if( its == find( itr, its, result2[i] ))
		{
			result1[res] = result2[i];
			res++;
			res %= n;
		}
		i++;	
	}
		
	// computing second child
	itr = result2.begin()+r;
	its = result2.begin()+s+1;
	
	i = s+1;
	res = s+1;
	while((i != s) || (res != r)){
		i %= n;
		if( its == find( itr, its, tmp1[i] ))
		{
			result2[res] = tmp1[i];
			res++;
			res %= n;
		}
		i++;	
	}

	return std::make_pair(permutation(result1), permutation(result2));
}

std::pair<permutation, permutation> crossover::random_cx(permutation& p1, permutation& p2)
{
	assert(p1.N() == p2.N());

	int n = p1.N();
	int r = rand() % n;
  int s = rand() % n;
  if(r > s)
    std::swap(r, s);
	
	std::vector<int> result1(p1.P().begin(), p1.P().end());
	std::vector<int> result2(p2.P().begin(), p2.P().end());


	return std::make_pair(permutation(result1), permutation(result2));
}

std::pair<permutation, permutation> crossover::random_pmx(permutation& p1, permutation& p2)
{
  assert(p1.N() == p2.N());

  int r = rand() % p1.N();
  int s = rand() % p1.N();
  if(r > s)
    std::swap(r, s);
  return partial_matched(p1, p2, r, s);
}

std::pair<permutation, permutation> crossover::partial_matched(permutation& p1, permutation& p2, int r, int s)
{
  assert(p1.N() == p2.N());

  std::vector<int> result1(p1.P().begin(), p1.P().end());
  std::vector<int> result2(p2.P().begin(), p2.P().end());

  const int empty = -1;
  // make range <r, s> empty
  for(int i = r; i < s + 1; ++i)
    result1[i] = result2[i] = empty;

  // generating result1 from <r,s> part of p2
  for(int i = r; i < s + 1; ++i)
  {
    int p_gene = p2.P()[i];
    int proposed_gene = p_gene;
    while(true)
    {
      if(result1.end() == find(result1.begin(), result1.end(), proposed_gene))
      {
        // no proposed_gene in result1
        result1[i] = proposed_gene;
        break;
      }
      else
      {
        // proposed_gene in result already
        // we should find new value

        proposed_gene = p2.P()[p1.elem_position(proposed_gene)];
      }
    }
  }

  // generating result2 from <r,s> part of p1
  for(int i = r; i < s + 1; ++i)
  {
    int p_gene = p1.P()[i];
    int proposed_gene = p_gene;
    while(true)
    {
      if(result2.end() == find(result2.begin(), result2.end(), proposed_gene))
      {
        // no proposed_gene in result1
        result2[i] = proposed_gene;
        break;
      }
      else
      {
        // proposed_gene in result already
        // we should find new value

        proposed_gene = p1.P()[p2.elem_position(proposed_gene)];
      }
    }
  }

  return std::make_pair(permutation(result1), permutation(result2));
}
