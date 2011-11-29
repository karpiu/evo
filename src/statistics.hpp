#pragma once

#include "permutation.hpp"
#include "sga.hpp"

namespace statistics
{
  int edit_distance( const permutation& a, const permutation& b );
  int variance( const population& p, const int i);
  int avg_specimen( const population& p);
}
