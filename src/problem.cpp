#include "problem.hpp"

config cfg;

int iter = 0;
population prev_population;

const int population_size = 100;
const int parents = population_size / 2;

int N;  // number of jobs
int M;  // number of machines

flowshop f;

void init_prev_population()
{
  for(int i = 0; i < population_size; ++i)
  {
    specimen s;
    s.perm = permutation(N);
    s.eval = s.adapt = 0.0;
    prev_population.push_back(s);
  }
}

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
  return f.cmax(p.P());
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
  return ++iter > cfg.max_iter;
}

bool smart_termination(const population& p)
{
  float sum = 0.0;
  for(int i=0; i<population_size; ++i)
    sum += abs(prev_population[i].eval - p[i].eval);
  prev_population = p;
  return sum < (population_size/2.0);
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

    auto desc = crossover::random_crossover(cfg.crossover_type, p[i].perm, p[j].perm);
    
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
    return std::less<float>()(s1.adapt, s2.adapt);
  }
};

void replacement(population& p)
{
  std::sort(p.begin(), p.end(), eval_cmp());
  p.resize(population_size);
}

void report(population& p)
{
  switch(cfg.report_every)
  {
    case config::report::none:
      break;
    case config::report::avg:
      {
        float avg = 0.0;
        for(auto i = p.begin(); i != p.end(); ++i)
          avg += i->eval;
        avg /= static_cast<float>(p.size());
        std::cout << iter << ' ' << avg << '\n';
      }
      break;
    case config::report::best:
      std::cout << iter << ' ' << p[0].eval << '\n';
      break;
  }
}

void report_end(population& p)
{
  if(cfg.report_every == config::report::none)
  {
    if(cfg.report_population)
    {
      if(cfg.debug)
      {
        std::cout << "Reporting population\n";
        std::cout << "Evaluation = [ permutation ]\n";
      }
      std::sort(p.begin(), p.end(), eval_cmp());
      for(auto i = p.begin(); i != p.end(); ++i)
        std::cout << i->eval << " = " << i->perm << std::endl;
    }

    if(cfg.report_best)
    {
      if(cfg.debug)
      {
        std::cout << "Reporting best speciman\n";
        std::cout << "Evaluation = [ permutation ]\n";
      }
      std::cout << p.begin()->eval << " = " << p.begin()->perm << std::endl;
    }
  }
}

void read_input()
{
  std::cin >> N;
  std::cin >> M;

  f.initialize(N,M);

  for(int x = 0; x < M; ++x)
    for(int y = 0; y < N; ++y)
      std::cin >> f[x][y];
}

void solve_flowshop(config& c)
{
  init_random();

  cfg = c;

  if(cfg.debug)
  {
    std::cout << "Crossover operator: ";
    switch(cfg.crossover_type)
    {
      case crossover::type::PMX:
        std::cout << "PMX";
        break;
      case crossover::type::CX:
        std::cout << "CX";
        break;
      case crossover::type::OX:
        std::cout << "OX";
        break;
    }
    std::cout << std::endl;
  }

  read_input();
  
  init_prev_population();

  sga algorithm;
  algorithm.initial_population = initial_population;
  algorithm.evaluate = evaluate_population;
  algorithm.adaptation = adapt_population;
  algorithm.termination = cfg.smart_termination ? smart_termination : termination;
  algorithm.mutation = mutation_function;
  algorithm.crossover = crossover_function;
  algorithm.replacement = replacement;
  algorithm.report = report;
  algorithm.report_end = report_end;
  algorithm.run();
}
