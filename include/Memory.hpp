#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <stdexcept>

class Memory {
public: 
    Memory(const size_t& memorySizeBytes) : m_memory(memorySizeBytes, 0) {}

    void load_binary(const std::vector<uint32_t>& instructionSet)
    {
        std::copy(instructionSet.begin(), instructionSet.end(), m_memory.begin());
    }

    const std::size_t sizeBytes() {
        return m_memory.size() * sizeof(uint32_t);
    }

    uint32_t& operator[](size_t address) {
        if ((address % 4) || 
            (address >= m_memory.size())) {
            throw std::out_of_range("Incorrect address");
        }
        return m_memory[address/4];
    }

    const uint32_t& operator[](size_t address) const {
        if ((address % 4) || 
            (address >= m_memory.size())) {
            throw std::out_of_range("Incorrect address");
        }
        return m_memory[address/4];
    }

    uint32_t read(const uint8_t& address) const {
        if ((address % 4) || 
            (address >= m_memory.size())) {
            throw std::out_of_range("Incorrect address");
        }
        return m_memory[address/4];
    }

    void write(const uint8_t& address, const uint32_t& data) {
        if ((address % 4) || 
            (address >= m_memory.size())) {
            throw std::out_of_range("Incorrect address");
        }
        m_memory[address/4] = data;
    }

private:
    std::vector<uint32_t> m_memory;
};

#endif // MEMORY_HPP