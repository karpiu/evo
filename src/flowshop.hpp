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
    void initialize(int n, int m);
    
    // access to time_table of machines through [] operator
    std::vector<int>& operator [] ( unsigned int n ) { assert(n < size); return machs[n].time_table; };

    int cmax(const std::vector<int> &v);  

    bool is_done() const { return idle; };
    bool is_ready() const { return ! machs[0].is_working; }; 
    unsigned long get_time() const { return time; };
    friend std::ostream& operator << (std::ostream& os, const flowshop& f);
};

