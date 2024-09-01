#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <iomanip>

class Log {
public: 
    Log(const std::string& filename); 

    ~Log();

    void trace(uint64_t cycle, uint32_t pc, uint32_t instruction, const std::string& regState);
    
private:
    std::ofstream logFile;
};

#endif  // LOG_HPP