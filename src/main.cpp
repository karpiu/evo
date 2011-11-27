#include <iostream>
#include <vector>
#include <functional>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "problem.hpp"
#include "crossover.hpp"


po::variables_map read_command_line(po::options_description command_line_args_desc, int argc, char* argv[])
{
  po::variables_map args;
  po::store(po::parse_command_line(argc, argv, command_line_args_desc), args);
  po::notify(args);
  
  return args;
}

po::options_description command_line_args_create()
{
  po::options_description command_line_args("Available options");

  command_line_args.add_options()
    ("help,h", "Produce help message.")
    ("debug,d", "Show assignment of command line parameters.")
    ("report-population,R", "Reports all population.")
    ("report-best,r", "Reports best found speciman.")
    ("report-every-frame,e", po::value<std::string>(), "Reports every frame. Available: best, avg.")
    ("max-iter,i", po::value<int>()->default_value(1000), "Maximum number of iterations.")
    ("crossover,x", po::value<std::string>()->default_value("pmx"), "Crossover operators. Available: pmx, cx, ox")
    ("smart-termination,t", "Use termination condition that does not depend on --max-iter. Also overrides --max-iter")
    ;
  return command_line_args;
}

config interpret_cmd_line_arguments(const po::variables_map& command_line_args)
{
  config c;
  
  assert(command_line_args.count("crossover"));
  const std::string crossover_operator = command_line_args["crossover"].as<std::string>();
  if(crossover_operator == "pmx")
    c.crossover_type = crossover::type::PMX;
  else if(crossover_operator == "ox")
    c.crossover_type = crossover::type::OX;
  else if(crossover_operator == "cx")
    c.crossover_type = crossover::type::CX;
  else
    throw std::runtime_error("Crossover operator unspecified.");

  if(command_line_args.count("debug"))
    c.debug = true;
  else
    c.debug = false;

  if(command_line_args.count("report-population"))
    c.report_population = true;
  else
    c.report_population = false;
  
  if(command_line_args.count("report-best"))
    c.report_best = true;
  else
    c.report_best = false;

  if(command_line_args.count("report-every-frame"))
  {
    const std::string to_report = command_line_args["report-every-frame"].as<std::string>();
    if(to_report == "best")
      c.report_every = config::report::best;
    else if(to_report == "avg")
      c.report_every = config::report::avg;
  }
  else
    c.report_every = config::report::none;
  
  if(command_line_args.count("smart-termination")) 
    c.smart_termination = true;
  else
    c.smart_termination = false;
  
  assert(command_line_args.count("max-iter"));
  c.max_iter = command_line_args["max-iter"].as<int>();
  return c;
}

void read_cmd_params(int argc, char* argv[])
{
  po::options_description command_line_args_desc = command_line_args_create();
  po::variables_map command_line_args = read_command_line(command_line_args_desc, argc, argv);

  if(command_line_args.count("crossover"))
  {
    const std::string crossover_operator = command_line_args["crossover"].as<std::string>();
    std::cout << "crossover operator: " << crossover_operator << std::endl;
  }

  if(command_line_args.count("help"))
  {
    std::cout << command_line_args_create() << "\n";
  }
}


int main(int argc, char* argv[])
{
  try
  {
    po::options_description command_line_args_desc = command_line_args_create();
    po::variables_map command_line_args = read_command_line(command_line_args_desc, argc, argv);

    if(command_line_args.count("help"))
    {
      std::cout << command_line_args_create() << "\n";
      return 0;
    }

    config cfg = interpret_cmd_line_arguments(command_line_args);
    solve_flowshop(cfg);
  }
  catch(std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
