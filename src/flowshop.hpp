#pragma once

#include <vector>

struct machine 
{
    int job;  // job id
    bool is_working;  // is it working on some job?
    int countdown; // time to completion
};

class flowshop
{
    std::vector<machine> machs;
    unsigned long time;
  
  public:
    flowshop(int m);
    ~flowshop() {}
}
