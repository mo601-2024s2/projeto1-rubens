#include "Log.hpp"

Log::Log(const std::string& filename) {
    logFile.open(filename);
    if (!logFile.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo de log: " << filename << std::endl;
    }
}

Log::~Log() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Log::trace(uint64_t cycle, uint32_t pc, uint32_t instruction, const std::string& regState) {
    if (logFile.is_open()) {
        logFile << std::hex << std::setw(10) << std::setfill('0') << cycle << " "
                << std::hex << std::setw(8) << std::setfill('0') << pc << " "
                << std::hex << std::setw(8) << std::setfill('0') << instruction << " "
                << regState << "\n";
    }
}