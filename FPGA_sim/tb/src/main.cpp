
#include "assert.h"
#include "product_sm_top_tb.h"
#include <klee/klee.h> 

uartTb* tb = NULL;
std::atomic<uint64_t>* execution_count = nullptr; 

double sc_time_stamp() { return tb->get_main_time(); }

int main(int argc, char** argv, char** env) {
  // Initialize shared execution counter
  InitializeExecutionCount();
    
  // Instantiate testbench
  tb = new uartTb(argc, argv);

  // Simulate the DUT
  tb->SimulateDUT();

  // Teardown
  delete (tb);
  tb = NULL;
  exit(0);
}
