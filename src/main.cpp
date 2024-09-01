#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

#include <bitset>

#include <config.hpp>
#include <RiscV.hpp>
#include <Memory.hpp>
#include <RegBank.hpp>
#include <Log.hpp>

std::vector<uint32_t> readObjFile(std::ifstream& objFile) {
    std::vector<uint32_t> instructionSet;
    uint32_t instruction {};

    while (objFile.read(reinterpret_cast<char*>(&instruction), sizeof(instruction))) {
        instructionSet.push_back(instruction);
    }
    objFile.close();
        
    return instructionSet;
};


int main(int argc, char* argv[]) {

    
    if (argc != 2 ) {
        std::cout << "Invalid input" << std::endl;
        return -1;
    }
    std::ifstream objFile(argv[1], std::ios::binary);

    if (!objFile) {
        std::cerr << "Error to open the binary file" << std::endl;
        return 1;
    }

    std::vector<uint32_t> instructionSet {readObjFile(objFile)}; // pass to in
    if (instructionSet.empty()) {
        std::cout << "Invalid instructionSet" << std::endl;
    }

    Memory memory(kMemorySizeBytes);
    memory.load_binary(instructionSet);
    
    uint32_t addr = 0;
    for (auto instruction: instructionSet) {
        std::cout << "addr:" << addr << "data: " << std::bitset<32>(instruction) << std::endl;
        addr += sizeof(instruction);
    }

    RegBank<uint32_t> regBank(kRegBankSize);
    Log riscVLog(kLogFileName);
    RiscV RiscVSim(memory, regBank, riscVLog);

    RiscVSim.run();
    // ProcessorDUT.execute(instructionSet);

    return 0;
}