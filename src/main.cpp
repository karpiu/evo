#include <iostream>
#include <vector>
#include "random.hpp"
#include "sga.hpp"

population initial_population()
{
  permutation p(5, permutation::type::random);

  population v;
  v.push_back(p);
  return v;
}

float evaluation(const permutation& p)
{
  return 0;
}

bool termination(const population& p)
{
  return true;
}

void mutation(population& p)
{
}

void crossover(population& p)
{
}

void replacement(population& p)
{
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
  algorithm.mutation = mutation;
  algorithm.crossover = crossover;
  algorithm.replacement = replacement;
  algorithm.raport = raport;
  algorithm.run();
  return 0;
}
