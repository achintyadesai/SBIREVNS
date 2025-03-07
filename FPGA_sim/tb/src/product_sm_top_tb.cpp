
#include "product_sm_top_tb.h"

#include <bitset>
#include <iostream>
#include <cstdlib>
#include <cstdint>

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>


// Constructor
uartTb::uartTb(int argc, char** argv) : STDINFuzzTb(argc, argv) {
  InitializeDUT();
    
}

// Destructor
uartTb::~uartTb() {}


std::vector<uint64_t> ReadMemoryFile64(const std::string& filename) {
    std::vector<uint64_t> values;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return values;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        uint64_t value;
        ss >> std::hex >> value; // Read hex as 64-bit
        values.push_back(value);
    }

    file.close();
    return values;
}
// read 32-bit value
std::vector<uint32_t> ReadMemoryFile32(const std::string& filename) {
    std::vector<uint32_t> values;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return values;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        uint32_t value;
        ss >> std::hex >> value; // Read hex as 32-bit
        values.push_back(value);
    }

    file.close();
    return values;
}


// Helper function to Write Values to BRAM
void uartTb::Write64BitValueToBRAM(uint32_t base_addr, uint64_t value, int offset, Vtop_product_sm_top_tb* dut) {
    uint32_t lower_bits = value & 0xFFFFFFFF; // Extract lower 32 bits
    uint32_t upper_bits = (value >> 32) & 0xFFFFFFFF; // Extract upper 32 bits

    // Write lower 32 bits
    dut->inferred_sm_bram_addr = base_addr + offset * 4;
    dut->inferred_sm_bram_din = lower_bits;
    dut->inferred_sm_bram_en = 1;
    dut->inferred_sm_bram_we = 0xF; // Write enable
    ToggleClock(&dut_.clk, 2);
    dut->inferred_sm_bram_en = 0;

    // Write upper 32 bits
    dut->inferred_sm_bram_addr = base_addr + (offset + 1) * 4;
    dut->inferred_sm_bram_din = upper_bits;
    dut->inferred_sm_bram_en = 1;
    dut->inferred_sm_bram_we = 0xF; // Write enable
    ToggleClock(&dut_.clk, 2);
    dut->inferred_sm_bram_en = 0;
}
void uartTb::Write32BitValueToBRAM(uint32_t base_addr, uint32_t value, int offset, Vtop_product_sm_top_tb* dut) {
    dut->sm_next_addr_bram_addr = base_addr + offset * 4;
    dut->sm_next_addr_bram_din = value;
    dut->sm_next_addr_bram_en = 1;
    dut->sm_next_addr_bram_we = 0xF; // Write enable
    ToggleClock(&dut_.clk, 2);
    dut->sm_next_addr_bram_en = 0;
}

//Initialize sm_value_init (64-bit Values)
void uartTb::InitializeSM() {
    std::vector<uint64_t> sm_value_init = ReadMemoryFile64("PATH_TO_SM_initialization_file");

    uint32_t base_addr = 0x40000000; // Base address for SM BRAM
    int offset = 0;

    for (const auto& value : sm_value_init) {
        Write64BitValueToBRAM(base_addr, value, offset, dut_.product_sm_top_tb);
        offset += 2; // Each 64-bit value occupies two 32-bit addresses
    }
}
//Initialize sm_next_addr_init and sm_next_addr (32-bit Values)
void uartTb::InitializeNextStateBRAM() {
    std::vector<uint32_t> sm_next_addr_init = ReadMemoryFile32("PATH_TO_product_sm_next_addr_bram_loc_file");
    std::vector<uint32_t> sm_next_addr = ReadMemoryFile32("PATH_TO_product_sm_next_addr_state_file");

    uint32_t base_addr = 0x42000000;
    int offset = 0;
    
    if (sm_next_addr_init.size() != sm_next_addr.size()) {
        std::cerr << "Error: Mismatched sizes between sm_next_addr_init and sm_next_addr!" << std::endl;
        return;
    }

    for (size_t i = 0; i < sm_next_addr_init.size(); i++) {
        Write32BitValueToBRAM(base_addr + (sm_next_addr[i] * 4), sm_next_addr_init[i], 0, dut_.product_sm_top_tb);
    }
}


// Initialize DUT inputs
void uartTb::InitializeDUT() {
  dut_.clk = 1;  
  dut_.rst = 1;
  
  dut_.product_sm_top_tb->can_id_val   = 0; //12-bit
  dut_.product_sm_top_tb->payload      = 0; //64-bit
  
  dut_.product_sm_top_tb->payload_major = 0; //8-bit
  dut_.product_sm_top_tb->payload_minor = 0; //8-bit
  
  dut_.product_sm_top_tb->pre_processing_top_i->msg_mode_reg = 0;
  
  dut_.eval();

  // Start time at 1 to align rising clock edges with even time values
  set_main_time(1);
}


uint32_t uartTb::GetAFLGeneratedID() {
    uint32_t event_id;
    uint8_t test_input[INPUT_PORT_SIZE_BYTES] = {0};
    
    ReadBytes(test_input, INPUT_PORT_SIZE_BYTES);
    
		for (int i = 0; i < INPUT_PORT_SIZE_BYTES && i < 4; ++i) { // Ensure we don't exceed 4 bytes
			event_id |= (static_cast<uint32_t>(test_input[i]) << (i * 4));
		}
   
    return event_id;
}

uint64_t uartTb::GetAFLGeneratedPayload() {
    uint64_t event_payload;
    uint8_t test_input[INPUT_PORT_SIZE_BYTES] = {0};
    
    ReadBytes(test_input, INPUT_PORT_SIZE_BYTES);
    
    for (int i = 0; i < INPUT_PORT_SIZE_BYTES && i < 8; ++i) { // Ensure we don't exceed 8 bytes
			event_payload |= (static_cast<uint64_t>(test_input[i]) << (i * 8));
		}
   
    return event_payload;
}

// Simulate the DUT with testbench input file
void uartTb::SimulateDUT() {
  // Create buffer for test data
  uint8_t test_input[INPUT_PORT_SIZE_BYTES] = {0};
  freopen("PATH_TO_AFL_output.txt","w",stdout);

  // Reset the DUT
  dut_.clk = 1;  
  dut_.rst = 1;
  dut_.arm_trigger = 0;
  
  ToggleClock(&dut_.clk, 10);
  
  dut_.rst = 0;
  
  // running tb
  std::cout << "*****VLT running the tb... *****\n" << std::endl;
  ToggleClock(&dut_.clk, 20);
  
  
  //Start Data Generation
  InitializeSM();
  InitializeNextStateBRAM();
  
  ToggleClock(&dut_.clk, 10);
  
  std::cout << "Preparing loading test inputs\n " << std::endl;
  dut_.arm_trigger = 1;
  if (execution_count) { // Ensure it is initialized
        std::cout << "\n***execution_count = " << *execution_count << "***" << std::endl;
  } else {
        std::cerr << "Error: execution_count is not initialized!" << std::endl;
  }
  
  //Load original trace
  std::vector<uint32_t> can_ID = ReadMemoryFile32("test_canID.txt");
  std::vector<uint64_t> can_payload = ReadMemoryFile64("test_payload.txt");
  
  const int K = 5; //injection frequency
  
  while (ReadBytes(test_input, INPUT_PORT_SIZE_BYTES) && !Verilated::gotFinish()) {
    //round++;
    
    for (size_t i = 0; i < can_ID.size(); ++i) {
        ToggleClock(&dut_.clk, 20);
        std::cout << "New input... Delay for 10 clock cycles " << std::endl;
        
        dut_.msg_valid = 1;
        
        if (((i+1) % K == 0)) {
            // Inject AFL-generated input
            std::cout << "Reaching pre defined " << K << " events, replace this event with AFL generated testcase\n";
            uint64_t payload = 0;
            for (int i = 0; i < INPUT_PORT_SIZE_BYTES && i < 8; ++i) { // Ensure we don't exceed 8 bytes
                payload |= (static_cast<uint64_t>(test_input[i]) << (i * 8));
            }
            dut_.payload = payload;
            
            // Extract 12-bit CAN ID value (last two bytes)
            uint16_t dut_can_id_val = (static_cast<uint16_t>(test_input[INPUT_PORT_SIZE_BYTES - 2]) << 8) |
                                      (static_cast<uint16_t>(test_input[INPUT_PORT_SIZE_BYTES - 1]));
            
            // Ensure only 12 bits are used
            dut_.can_id_val = dut_can_id_val & 0x0FFF;
        } else {
            dut_.can_id_val = can_ID[i];
            dut_.payload = can_payload[i];
        }
        ToggleClock(&dut_.clk, 2);
               
        dut_.msg_valid = 0;
        }
    
        std::cout << std::endl;
   }
    

  // Final model cleanup
  dut_.final();
}
