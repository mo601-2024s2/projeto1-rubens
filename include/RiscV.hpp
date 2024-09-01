#include <cstdint>
#include <vector>
#include <iostream>
#include "Memory.hpp"
#include "RegBank.hpp"
#include "Log.hpp"
#include "Instruction.hpp"
#include "Timer.hpp"

class RiscV {
public: 
    RiscV(Memory& inputMemory,
          RegBank<uint32_t> inputRegBank,
          Log& inputLog) : 
        m_memory(inputMemory),
        m_regbank(inputRegBank),
        m_log(inputLog) {}

    void run();

private:

    void fetch();
    void execute();

    Memory& m_memory;
    RegBank<uint32_t>& m_regbank;
    Log& m_log;

    uint32_t m_pc{0};  // program counter
    uint32_t m_binary{0};
    Instruction* m_instruction;
};