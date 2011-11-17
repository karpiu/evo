#include <iostream>
#include <vector>
#include <functional>
#include "random.hpp"
#include "sga.hpp"
#include "mutation.hpp"
#include "crossover.hpp"

const int population_size = 100;
const int parents = population_size / 2;
int N = 5;

const int MAX_N = 100;
int a[MAX_N][MAX_N];
int b[MAX_N][MAX_N];

std::vector<float> evaluation_set;
std::vector<float> adaptation_set;

population initial_population()
{
  population pop;
  for(int i = 0; i < population_size; ++i)
	{
		specimen s;
		s.perm = permutation(N, permutation::type::random);
		s.eval = s.adapt = 0.0;    
		pop.push_back(s);
	}  
	return pop;
}

float evaluation(const permutation& p)
{
  int sum = 0;
  for(int i = 0; i < N; ++i)
    for(int j = i+1; j < N; ++j)
      sum += a[i][j] * b[p.P()[i]][p.P()[j]];
  return sum;
}

void evaluate_population(population& p)
{
	for(int i=0; i<population_size; i++)
		p[i].eval = evaluation(p[i].perm);
}

bool elav_comp(specimen a, specimen b) { return a.eval<b.eval; }

void adapt_population(population& p)
{
	float F_min = (*min_element(p.begin(),p.end(),elav_comp)).eval;
	for(int i=0; i<population_size; i++)
	{
		float sum = 0.0;
		for(int j=0; j<population_size; j++)
			sum += p[j].eval - F_min;
		p[i].adapt = (p[i].eval - F_min)/sum;
	}
}

bool termination(const population& p)
{
  static int iter = 0;
  return ++iter > 1000;
}

void mutation_function(population& p)
{
  for(auto i = p.begin(); i != p.end(); ++i)
  {
    mutation::random_transposition((*i).perm);
  }
}

void crossover_function(population& p)
{
  population new_population;

  for(int i = 0; i < parents; ++i)
  {
    const int a = rand() % N;
    const int b = rand() % N;

    auto desc = crossover::random_pmx(p[a].perm, p[b].perm);
		
		specimen ch1, ch2;
		ch1.perm = desc.first; 
		ch1.eval = ch1.adapt = 0.0;
		ch2.perm = desc.second;
		ch2.eval = ch2.adapt = 0.0;

    new_population.push_back(ch1);
    new_population.push_back(ch2);
  }

  p.insert(p.end(), new_population.begin(), new_population.end());
}

struct eval_cmp
{
  bool operator()(const specimen& s1, const specimen& s2) const
  {
    return std::less<float>()(s1.eval, s2.eval);
  }
};

void replacement(population& p)
{
  std::sort(p.begin(), p.end(), eval_cmp());
  p.resize(population_size);
}

void raport(population& p)
{
  std::cout << "Raporting population\n";
	std::sort(p.begin(), p.end(), eval_cmp());
  for(auto i = p.begin(); i != p.end(); ++i)
    std::cout << (*i).eval << " = " << (*i).perm << std::endl;
}

void read_input()
{
  std::cin >> N;

  for(int x = 0; x < N; ++x)
    for(int y = 0; y < N; ++y)
      std::cin >> b[x][y];

  for(int x = 0; x < N; ++x)
    for(int y = 0; y < N; ++y)
      std::cin >> a[x][y];
}

int main(int argc, char* argv[])
{
  init_random();

  read_input();

  sga algorithm;
  algorithm.initial_population = initial_population;
	algorithm.evaluate = evaluate_population;
	algorithm.adaptation = adapt_population;
  algorithm.termination = termination;
  algorithm.mutation = mutation_function;
  algorithm.crossover = crossover_function;
  algorithm.replacement = replacement;
  algorithm.raport = raport;
  algorithm.run();
  return 0;
}
