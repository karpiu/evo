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

population initial_population()
{
  population pop;
  for(int i = 0; i < population_size; ++i)
    pop.push_back(permutation(N, permutation::type::random));
  return pop;
}

float evaluation(const permutation& p)
{
  return 0;
}

bool termination(const population& p)
{
  static int iter = 0;
  return ++iter > 10;
}

void mutation_function(population& p)
{
  for(auto i = p.begin(); i != p.end(); ++i)
  {
    mutation::random_transposition(*i);
  }
}

void crossover_function(population& p)
{
  population new_population;

  for(int i = 0; i < parents; ++i)
  {
    const int a = rand() % N;
    const int b = rand() % N;

    auto desc = crossover::random_pmx(p[a], p[b]);
    new_population.push_back(desc.first);
    new_population.push_back(desc.second);
  }

  p.insert(p.end(), new_population.begin(), new_population.end());
}

struct eval_cmp
{
  bool operator()(const permutation& p1, const permutation& p2) const
  {
    return std::less<float>()(evaluation(p1), evaluation(p2));
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
  for(auto i = p.begin(); i != p.end(); ++i)
    std::cout << *i << std::endl;
}

int main(int argc, char* argv[])
{
  init_random();

  sga algorithm;
  algorithm.initial_population = initial_population;
  algorithm.termination = termination;
  algorithm.evaluation = evaluation;
  algorithm.mutation = mutation_function;
  algorithm.crossover = crossover_function;
  algorithm.replacement = replacement;
  algorithm.raport = raport;
  algorithm.run();
  return 0;
}
