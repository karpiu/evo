#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <math.h>

struct machine 
{
  int job;  // job id
  bool is_working;  // is it working on some job?
  int countdown; // time to completion
  std::vector<int> time_table;
  
  machine(int jobs)
  {
    job = 0;
    is_working = false;
    countdown = 0;
    time_table = std::vector<int>(jobs,0);
  }
  
  ~machine(){ }
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
    unsigned int size;
    bool idle;    
    
  public:
    flowshop();
    flowshop(int n, int m);
    flowshop(const flowshop &f);
    ~flowshop() {}
    
    // access to time_table of machines through [] operator
    std::vector<int>& operator [] ( unsigned int n ) { assert(n < size); return machs[n].time_table; };

    void run(std::queue<int> &q);

    void add_job(int job);    
    void update();
    void clear_flow();
    
    int cmax(const std::vector<int> &v);  

    bool is_done() { return idle; };
    bool is_ready() { return ! machs[0].is_working; }; 
    unsigned long get_time() { return time; };
    friend std::ostream& operator << (std::ostream& os, const flowshop& f);
};

