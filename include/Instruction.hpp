#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include "Memory.hpp"
#include "RegBank.hpp"
#include <iostream>

static constexpr uint32_t kOpCodeMask = 0x7F;  // basic operation code
static constexpr uint32_t kRdMask = 0x1F;  // destination
static constexpr uint32_t kRdShift = 7;
static constexpr uint32_t kRs1Mask = 0x1F;  // first operand
static constexpr uint32_t kRs1Shift = 15;
static constexpr uint32_t kRs2Mask = 0x1F;  // psecond operand
static constexpr uint32_t kRs2Shift = 20;

// R
static constexpr uint32_t kFunc3RMask = 0x7;  // aditional 3-bits OpCode 
static constexpr uint32_t kFunc3RShift = 12;
static constexpr uint32_t kFunc7RMask = 0x7F;  // aditional 7-bits OpCode 
static constexpr uint32_t kFunc7RShift = 25;

// I
static constexpr uint32_t kImmIMask = 0xFFF; // Immediate[11:0]
static constexpr uint32_t kImmIShift = 20;

// S
static constexpr uint32_t kImm1SMask = 0x1F;  // Immediate [4:0]
static constexpr uint32_t kImm1SShift = 7;
static constexpr uint32_t kImm2SMask = 0x7F;  // Immediate [11:5]
static constexpr uint32_t kImm2SShift = 25;

// SB or B?
static constexpr uint32_t kImm1SBMask = 0x3F;  // Immediate [4:1]
static constexpr uint32_t kImm1SBShift = 7;
static constexpr uint32_t kImm2SBMask = 0x1;  // Immediate [10:5]
static constexpr uint32_t kImm2SBShift = 31;

// U
static constexpr uint32_t kImmUMask = 0xFFFFF;  // Immediate [31:12]
static constexpr uint32_t kImmUShift = 12;

// UJ or J?
static constexpr uint32_t kImm1UJMask = 0xFF;
static constexpr uint32_t kImm1UJShift = 12;
static constexpr uint32_t kImm2UJMask = 0x1;
static constexpr uint32_t kImm2UJShift = 20;
static constexpr uint32_t kImm3UJMask = 0x3FF;
static constexpr uint32_t kImm3UJShift = 21;
static constexpr uint32_t kImm4UJMask = 0x1;
static constexpr uint32_t kImm4UJShift = 33;


// OPCODE TYPE
static constexpr uint8_t RTypeOpCode = 0x33; // OpCode - R-Type
static constexpr uint8_t IType1OpCode = 0x13 ;
static constexpr uint8_t IType2OpCode = 0x03; // OpCodes - I-Type
static constexpr uint8_t STypeOpCode = 0x23; // OpCode - S-Type
static constexpr uint8_t BTypeOpCode = 0x63; // OpCode - B-Type
static constexpr uint8_t UType1OpCode = 0x37 ;
static constexpr uint8_t UType2OpCode = 0x17; // OpCodes - U-Type
static constexpr uint8_t JTypeOpCode = 0x6F; // OpCode - J-Type

/*
OPCODES
*/
//RTYPE
static constexpr uint32_t kSLLICode = 0b00000000010010011;
static constexpr uint32_t kSRLICode = 0b00000001010010011;
static constexpr uint32_t kSRAICode = 0b01000001010010011;

static constexpr uint32_t kADDCode = 0b00000000000110011;
static constexpr uint32_t kSUBCode = 0b01000000000110011;
static constexpr uint32_t kSLLCode = 0b00000000010110011;
static constexpr uint32_t kSLTCode = 0b00000000100110011;
static constexpr uint32_t kSLTUCode = 0b00000000110110011;
static constexpr uint32_t kXORCode = 0b00000001000110011;
static constexpr uint32_t kSRLCode = 0b00000001010110011;
static constexpr uint32_t kSRACode = 0b01000001010110011;
static constexpr uint32_t kORCode = 0b00000001100110011;
static constexpr uint32_t kANDCode = 0b00000001110110011;
// MULT
static constexpr uint32_t kMULCode = 0b0000110011;
static constexpr uint32_t kMULHCode = 0b0010110011;
static constexpr uint32_t kMULHSUCode = 0b0100110011;
static constexpr uint32_t kMULHUCode = 0b0110110011;
static constexpr uint32_t kDIVCode = 0b1000110011;
static constexpr uint32_t kDIVUCode = 0b1010110011;
static constexpr uint32_t kREMCode = 0b1100110011;
static constexpr uint32_t kREMUCode = 0b1110110011;


// U-Type
static constexpr uint32_t kLUICode = 0b0110111;
static constexpr uint32_t kAUIPCCode = 0b0010111;

// J-Type
static constexpr uint32_t kJALCode = 0b1101111;

// IType
static constexpr uint32_t kJALRCode = 0b0001100111;
static constexpr uint32_t kLBCode = 0b0000000011;
static constexpr uint32_t kLHCode = 0b0010000011;
static constexpr uint32_t kLWCode = 0b0100000011;
static constexpr uint32_t kLBUCode = 0b1000000011;
static constexpr uint32_t kLHUCode = 0b1010000011;
static constexpr uint32_t kADDICode = 0b0000010011;
static constexpr uint32_t kSLTICode = 0b0100010011;
static constexpr uint32_t kSLTIUCode = 0b0110010011;
static constexpr uint32_t kXORICode = 0b1000010011;
static constexpr uint32_t kORICode = 0b1100010011;
static constexpr uint32_t kANDICode = 0b1110010011;
static constexpr uint32_t kFENCECode = 0b0000001111;
static constexpr uint32_t kFENCE_ICode = 0b0010001111;
static constexpr uint32_t kSCALLCode = 0b0001110011;
static constexpr uint32_t kSBREAKCode = 0b0001110011;

// BType
static constexpr uint32_t kBEQCode = 0b0001100011;
static constexpr uint32_t kBNECode = 0b0011100011;
static constexpr uint32_t kBLTCode = 0b1001100011;
static constexpr uint32_t kBGECode = 0b1011100011;
static constexpr uint32_t kBLTUCode = 0b1101100011;
static constexpr uint32_t kBGEUCode = 0b1111100011;


// SType
static constexpr uint32_t kSBCode = 0b000100011;
static constexpr uint32_t kSHCode = 0b0010100011;
static constexpr uint32_t kSWCode = 0b0100100011;


class Instruction
{
public:
    virtual ~Instruction() = default;

    virtual void decode(const uint32_t& binary) = 0;
    virtual void execute(Memory& memory,
                         RegBank<uint32_t>& regbank,
                         uint32_t& pc) = 0;
};


class InstructionR : public Instruction
{
public:
    void decode(const uint32_t& binary) override;
    void execute(Memory& memory,
                         RegBank<uint32_t>& regbank,
                         uint32_t& pc) override;

private:
    uint8_t m_opcode, m_rd, m_func3, m_rs1, m_rs2, m_func7;
    uint32_t m_instructionOpCode;
};

class InstructionI : public Instruction
{
public:
    void decode(const uint32_t& binary) override;
    void execute(Memory& memory,
                         RegBank<uint32_t>& regbank,
                         uint32_t& pc) override;

private:
    uint8_t m_opcode, m_rd, m_func3, m_rs1, m_imm;
    uint32_t m_instructionOpCode;
};

class InstructionS : public Instruction
{
public:
    void decode(const uint32_t& binary) override;
    void execute(Memory& memory,
                         RegBank<uint32_t>& regbank,
                         uint32_t& pc) override;

private:
    uint8_t m_opcode, m_imm, m_func3, m_rs1, m_rs2;
    uint32_t m_instructionOpCode;
};

class InstructionSB : public Instruction
{
public:
    void decode(const uint32_t& binary) override;
    void execute(Memory& memory,
                         RegBank<uint32_t>& regbank,
                         uint32_t& pc) override;

private:
    uint8_t m_opcode, m_imm, m_func3, m_rs1, m_rs2;
    uint32_t m_instructionOpCode;
};

class InstructionU : public Instruction
{
public:
    void decode(const uint32_t& binary) override;
    void execute(Memory& memory,
                         RegBank<uint32_t>& regbank,
                         uint32_t& pc) override;

private:
    uint8_t m_opcode, m_rd, m_imm;
};

class InstructionUJ : public Instruction
{
public:
    void decode(const uint32_t& binary) override;
    void execute(Memory& memory,
                         RegBank<uint32_t>& regbank,
                         uint32_t& pc) override;

private:
    uint8_t m_opcode, m_rd, m_imm;
};

#endif  // INSTRUCTION_HPP 