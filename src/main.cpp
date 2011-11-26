#include <iostream>
#include <vector>
#include <functional>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "problem.hpp"


po::variables_map read_command_line(po::options_description command_line_args_desc, int argc, char* argv[])
{
  po::variables_map args;
  po::store(po::parse_command_line(argc, argv, command_line_args_desc), args);
  po::notify(args);
  
  return args;
}

po::options_description command_line_args_create()
{
  po::options_description command_line_args("Available actions");

  command_line_args.add_options()
    ("help,h", "produce help message")
    ("crossover,x", po::value<std::string>()->default_value("pmx"), "Crossover operators. Available: pmx, cx, ox")
    ;
  return command_line_args;
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
    read_cmd_params(argc, argv);
    solve_flowshop();
  }
  catch(std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
