#pragma once

#include <vector>
#include <iostream>

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
    int size;
    bool idle;    
    
  public:
    flowshop(int m);
    ~flowshop() {}

    void update();
    bool isDone();
}
