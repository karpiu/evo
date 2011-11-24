#pragma once

#include <vector>
#include <iostream>

struct machine 
{
  int job;  // job id
  bool is_working;  // is it working on some job?
  int countdown; // time to completion
  int * time_table;
  
  machine(int jobs)
  {
    job = 0;
    is_working = false;
    contdown = 0;
    time_table = new int[jobs];
  }
  
  ~machine()
  {
    delete [] time_table;
  }
};

/*
 * flowshop class:
 * - represantation of M machines
 * - simulation of flow-shop jobs evaluation
 */

class flowshop
{
    std::vector<machine> machs;
    unsigned long time;
    int size;
    bool idle;    
    
  public:
    flowshop();
    flowshop(int n, int m);
    flowshop(const flowshop &f);
    ~flowshop() {}
    
    void run(std::queue<int> &q);

    void add_job();    
    void update();
    void clear_flow();

    bool is_done() { return idle; };
    bool is_ready() { return ! machs[0].is_working; }; 
    unsigned long get_time() { return time; };
};

