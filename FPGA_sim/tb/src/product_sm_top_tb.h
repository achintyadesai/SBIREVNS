
#ifndef UART_TB_H_
#define UART_TB_H_

#include "../include/stdin_fuzz_tb.h"

#include "Vtop.h" 
#include "Vtop_product_sm_top_tb.h"
#include "Vtop_product_sm_top.h"
#include "Vtop_pre_processing_top.h"

#include <atomic>
#include <sys/mman.h>

extern std::atomic<uint64_t>* execution_count;

inline void InitializeExecutionCount() {
    void* shared_mem = mmap(nullptr, sizeof(std::atomic<uint64_t>), PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    execution_count = new (shared_mem) std::atomic<uint64_t>(0); // Placement new to initialize
}

// Increment in your loop
inline void IncrementExecutionCount() {
    execution_count->fetch_add(1, std::memory_order_relaxed);
}


// DUT parameters
#define INPUT_PORT_SIZE_BYTES 8 
#define NUM_RESET_CLK_PERIODS 1

class uartTb : public STDINFuzzTb {
 public:
  uartTb(int argc, char** argv);
  ~uartTb();
  void SimulateDUT();
  
  void Write64BitValueToBRAM(uint32_t base_addr, uint64_t value, int offset, Vtop_product_sm_top_tb* dut);
  void Write32BitValueToBRAM(uint32_t base_addr, uint32_t value, int offset, Vtop_product_sm_top_tb* dut);
  void InitializeSM();
  void InitializeNextStateBRAM();
    
  uint32_t GetAFLGeneratedID();
  uint64_t GetAFLGeneratedPayload();

 private:
  void InitializeDUT();
};

#endif
