#include <iostream>
#include <vector>
#include <functional>
#include "random.hpp"
#include "sga.hpp"
#include "mutation.hpp"
#include "crossover.hpp"

const int population_size = 100;
const int parents = population_size / 2;

int N = 5;  // number of jobs
int M = 5;  // number of machines

const int MAX_N = 100;
const int MAX_M = 20;
int a[MAX_M][MAX_N]; // input data

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
  int time = 0;
  
  std::queue<int> q(p.P()); //  jobs queue
  flow_shop machines(M);   
  
  while( !q.empty() && !machines.finished() ) {
    
  }
  
  return time;
}

void evaluate_population(population& p)
{
  for(unsigned int i=0; i<p.size(); i++)
    p[i].eval = evaluation(p[i].perm);
}

bool eval_comp(specimen a, specimen b) { return a.eval<b.eval; }

void adapt_population(population& p)
{
  float F_min = min_element(p.begin(),p.end(),eval_comp)->eval;
  for(unsigned int i=0; i<p.size(); i++)
  {
    float sum = 0.0;
    for(unsigned int j=0; j<p.size(); j++)
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
    float prob = 1 - i->adapt; // probability of mutation
    float r = uniform_random(); // random float between <0,1)

    if(r < prob)
    {
      mutation::random_transposition(i->perm);
      i->eval = evaluation(i->perm); // after mutation is done we have to evaluate this specimen again
    }
  }
}

void crossover_function(population& p)
{
  population new_population;

  for(int i = 0; i < parents; ++i)
  {
    const int i = rand() % population_size;
    const int j = rand() % population_size;

    const float crossover_prob = 0.2f;

    if(abs(p[i].adapt - p[j].adapt) > crossover_prob)
      continue;

    auto desc = crossover::random_crossover(crossover::PMX, p[i].perm, p[j].perm);

    specimen ch1, ch2;
    ch1.perm = desc.first;
    ch1.eval = evaluation(ch1.perm);
    ch1.adapt = 0.0;
    ch2.perm = desc.second;
    ch2.eval = evaluation(ch2.perm);
    ch2.adapt = 0.0;

    new_population.push_back(ch1);
    new_population.push_back(ch2);
  }

  p.insert(p.end(), new_population.begin(), new_population.end());
}

struct eval_cmp
{
  bool operator()(const specimen& s1, const specimen& s2) const
  {
    return std::less<float>()(s2.adapt, s1.adapt);
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
    std::cout << i->eval << " = " << i->perm << std::endl;
}

void read_input()
{
  std::cin >> N;
  std::cin >> M;

  for(int x = 0; x < M; ++x)
    for(int y = 0; y < N; ++y)
      std::cin >> a[x][y];
  
  //std::cout<< N << " " << M << std::endl;
  //for(int x = 0; x < M; ++x)
  //{
  //  for(int y = 0; y < N; ++y)
  //    std::cout << a[x][y] << " ";
  //  std::cout << "\n";
  //}  
  //exit(0);
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
