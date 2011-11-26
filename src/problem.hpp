#include <iostream>
#include <vector>
#include <functional>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "random.hpp"
#include "sga.hpp"
#include "mutation.hpp"
#include "crossover.hpp"
#include "flowshop.hpp"

void solve_flowshop(const po::variables_map& command_line_args);
