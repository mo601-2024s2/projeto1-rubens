#ifndef REGBANK_HPP
#define REGBANK_HPP

#include <cstdint>
#include <vector>
#include <config.hpp>
#include <stdexcept>

template<typename T>
class RegBank {
public: 
    RegBank(const size_t& size) : m_regbank(size) {}

    T read(const uint32_t& reg) {
        return m_regbank[reg];
    };

    T& operator[](size_t index) {
        if (index >= m_regbank.size()) {
            throw std::out_of_range("Index out of range");
        }
        return m_regbank[index];
    }

    const T& operator[](size_t index) const {
        if (index >= m_regbank.size()) {
            throw std::out_of_range("Index out of range");
        }
        return m_regbank[index];
    }

    void write(const uint32_t& reg, const T& value) {
        m_regbank[reg] = value;
    };

private:

    std::vector<T> m_regbank;
    // uint32_t pcR;
};

#endif // REGBANK_HPP