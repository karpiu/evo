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

population initial_population()
{
  population pop;
  for(int i = 0; i < population_size; ++i)
    pop.push_back(permutation(N, permutation::type::random));
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

bool termination(const population& p)
{
  static int iter = 0;
  return ++iter > 1000;
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
    std::cout << evaluation(*i) << " = " << *i << std::endl;
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
  algorithm.termination = termination;
  algorithm.mutation = mutation_function;
  algorithm.crossover = crossover_function;
  algorithm.replacement = replacement;
  algorithm.raport = raport;
  algorithm.run();
  return 0;
}
