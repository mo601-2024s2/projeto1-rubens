
#include <Instruction.hpp>

void InstructionR::decode(const uint32_t& binary)
{
    m_opcode = binary & kOpCodeMask;
    m_rd = (binary >> kRdShift) & kRdMask;
    m_func3 = (binary >> kFunc3RShift) & kFunc3RMask;
    m_rs1 = (binary >> kRs1Shift) & kRs1Mask;
    m_rs2 = (binary >> kRs2Shift) & kRs2Mask;
    m_func7 = (binary >> kFunc7RShift) & kFunc7RMask;

    m_instructionOpCode = m_opcode | 
                          (m_func3 << 7) |
                          (m_func3 << 10);
}

void InstructionR::execute(Memory& memory, RegBank<uint32_t>& regbank, uint32_t& pc)
{
    switch (m_instructionOpCode)
    {
    
    case (kSLLICode):
        regbank[m_rd] = regbank[m_rs1] << m_rs2;
        break;
    case (kSRLICode):
        regbank[m_rd] = static_cast<unsigned int>(regbank[m_rs1]) >> m_rs2;
        break;
    case (kSRAICode):
        regbank[m_rd] = regbank[m_rs1] >> m_rs2;
        break;
    // SRAI, SLLI, SRLI NAO SAO R, MAS VOU CONSIDERAR shamt como rs2
    case (kADDCode):
        regbank[m_rd] = regbank[m_rs1] + regbank[m_rs2];
        break;
    case (kSUBCode):
        regbank[m_rd] = regbank[m_rs1] - regbank[m_rs2];
        break;
    case (kSLLCode):
        regbank[m_rd] = regbank[m_rs1] << regbank[m_rs2];
        break;
    case (kSLTCode):
        regbank[m_rd] = (regbank[m_rs1] < regbank[m_rs2]) ? 1 : 0;
        break;
    case (kSLTUCode):
        regbank[m_rd] = (static_cast<unsigned int>(regbank[m_rs1]) < static_cast<unsigned int>(regbank[m_rs2])) ? 1 : 0;
        break;
    case (kXORCode):
        regbank[m_rd] = regbank[m_rs1] ^ regbank[m_rs2];
        break;
    case (kSRLCode):
        regbank[m_rd] = regbank[m_rs1] >> m_rs2;
        break;
    case (kSRACode):
        regbank[m_rd] = regbank[m_rs1] >> regbank[m_rs2];
        break;
    case (kORCode):
        regbank[m_rd] = regbank[m_rs1] | regbank[m_rs2];
        break;
    case (kANDCode):
        regbank[m_rd] = regbank[m_rs1] & regbank[m_rs2];
        break;
    }
    std::cout << "InstructionR\n" << std::endl;
}
// -------------------------------------------------
void InstructionI::decode(const uint32_t& binary)
{
    m_opcode = binary & kOpCodeMask;
    m_rd = (binary >> kRdShift) & kRdMask;
    m_func3 = (binary >> kFunc3RShift) & kFunc3RMask;
    m_rs1 = (binary >> kRs1Shift) & kRs1Mask;
    m_imm = (binary >> kImmIShift) & kImmIMask;

    m_instructionOpCode = m_opcode |
                          (m_func3 << 7);
}

void InstructionI::execute(Memory& memory, RegBank<uint32_t>& regbank, uint32_t& pc)
{
    switch (m_instructionOpCode)
    {
    case (kJALRCode):
        {
            int32_t target = regbank[m_rs1] + m_imm;
            regbank[m_rd] = pc + 4;  // TODO: check reg[0] guarda PC
            regbank[0] = target;
        }
        break;
    case (kLBCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes()) {
                regbank[m_rd] = static_cast<int8_t>(memory[address]);
            }
        }
        break;
    case (kLHCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes() - 1) {
                regbank[m_rd] = static_cast<int16_t>(memory[address] | (memory[address + 1] << 8));
            }
        }
        break;
    case (kLWCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes() - 3) {
                regbank[m_rd] = static_cast<int32_t>(memory[address] | (memory[address + 1] << 8) | 
                                                    (memory[address + 2] << 16) | (memory[address + 3] << 24));
            }
        }
        break;
    case (kLBUCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes()) {
                regbank[m_rd] = static_cast<uint8_t>(memory[address]);
            }
        }
        break;
    case (kLHUCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes() - 1) {
                regbank[m_rd] = static_cast<uint16_t>(memory[address] | (memory[address + 1] << 8));
            }
        }
        break;
    case (kADDICode):
        regbank[m_rd] = regbank[m_rs1] + m_imm;
        break;
    case (kSLTICode):
        regbank[m_rd] = (regbank[m_rs1] < m_imm) ? 1 : 0;
        break;
    case (kSLTIUCode):
        regbank[m_rd] = (static_cast<uint32_t>(regbank[m_rs1]) < static_cast<uint32_t>(m_imm)) ? 1 : 0;
        break;
    case (kXORICode):
        regbank[m_rd] = regbank[m_rs1] ^ m_imm;
        break;
    case (kORICode):
        regbank[m_rd] = regbank[m_rs1] | m_imm;
        break;
    case (kANDICode):
        regbank[m_rd] = regbank[m_rs1] & m_imm;
        break;
    case (kFENCECode):
        break;
    case (kFENCE_ICode):
        break;
    case (kSCALLCode):
        if (m_imm == 0) {  // ECALL
            
        } else if (m_imm == 1) {  //EBREAK

        }
        break;
    default:
        break;
    }
    std::cout << "InstructionR\n" << std::endl;
}
// -------------------------------------------------
void InstructionS::decode(const uint32_t& binary)
{
    m_opcode = binary & kOpCodeMask;
    m_func3 = (binary >> kFunc3RShift) & kFunc3RMask;
    m_rs1 = (binary >> kRs1Shift) & kRs1Mask;
    m_rs2 = (binary >> kRs2Shift) & kRs2Mask;
    m_imm = ((binary >> 7) & 0x1F) | 
            (((binary >> 25) & 0x7F) << 5) ;

    m_instructionOpCode = m_opcode |
                          (m_func3 << 7);
}

void InstructionS::execute(Memory& memory, RegBank<uint32_t>& regbank, uint32_t& pc)
{
    switch (m_instructionOpCode)
    {
    case (kSBCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes()) {
                memory[address] = regbank[m_rs2] & 0xFF;  // LSB
            }
        }
        break;
    case (kSHCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes() - 1) {
                memory[address] = regbank[m_rs2] & 0xFF;              // LSB
                memory[address + 1] = (regbank[m_rs2] >> 8) & 0xFF;
            }
        }
        break;
    case (kSWCode):
        {
            int32_t address = regbank[m_rs1] + m_imm;
            if (address >= 0 && address < memory.sizeBytes() - 3) {
                memory[address] = regbank[m_rs2] & 0xFF;              // LSB
                memory[address + 1] = (regbank[m_rs2] >> 8) & 0xFF;
                memory[address + 2] = (regbank[m_rs2] >> 16) & 0xFF;
                memory[address + 3] = (regbank[m_rs2] >> 24) & 0xFF;  // Byte mais significativo
            }
        }
        break;
    default:
        break;
    }
}
// -------------------------------------------------
void InstructionSB::decode(const uint32_t& binary)
{
    m_opcode = binary & kOpCodeMask;
    m_func3 = (binary >> kFunc3RShift) & kFunc3RMask;
    m_rs1 = (binary >> kRs1Shift) & kRs1Mask;
    m_rs2 = (binary >> kRs2Shift) & kRs2Mask;
    m_imm = (((binary >> 7) & 0x1) << 11) | 
            (((binary >> 8) & 0xF) << 1) | 
            (((binary >> 25) & 0x3F) << 5) |  
            (((binary >> 31) & 0x1) << 12);

    m_instructionOpCode = m_opcode |
                          (m_func3 << 7);
}
void InstructionSB::execute(Memory& memory, RegBank<uint32_t>& regbank, uint32_t& pc)
{
    switch (m_instructionOpCode)
    {
    case (kBEQCode):
        if (regbank[m_rs1] == regbank[m_rs2]) {
            pc += m_imm;
        }
        break;
    case (kBNECode):
        if (regbank[m_rs1] != regbank[m_rs2]) {
            pc += m_imm;
        }
        break;
    case (kBLTCode):
        if (regbank[m_rs1] < regbank[m_rs2]) {
            pc += m_imm;
        }
        break;
    case (kBGECode):
        if (regbank[m_rs1] >= regbank[m_rs2]) {
            pc += m_imm;
        }
        break;
    case (kBLTUCode):
        if (static_cast<uint32_t>(regbank[m_rs1]) < static_cast<uint32_t>(regbank[m_rs2])) {
            pc += m_imm;
        }
        break;
    case (kBGEUCode):
        if (static_cast<uint32_t>(regbank[m_rs1]) >= static_cast<uint32_t>(regbank[m_rs2])) {
            pc += m_imm;
        }
        break;
    default:
        break;
    }    
}
// -------------------------------------------------
void InstructionU::decode(const uint32_t& binary)
{
    m_opcode = binary & kOpCodeMask;
    m_rd = (binary >> kRdShift) & kRdMask;
    m_imm = (((binary >> 12) & 0xFFFFF) << 12);
}
void InstructionU::execute(Memory& memory, RegBank<uint32_t>& regbank, uint32_t& pc)
{
    switch (m_opcode)
    {
    case (kLUICode):
        regbank[m_rd] = m_imm << 12;
        break;
    case (kAUIPCCode):
        regbank[m_rd] = pc + (m_imm << 12);
        break;
    default:
        break;
    }
}
// -------------------------------------------------
void InstructionUJ::decode(const uint32_t& binary)
{
    m_opcode = binary & kOpCodeMask;
    m_rd = (binary >> kRdShift) & kRdMask;
    m_imm = (((binary >> 12) & 0xFF) << 12) | 
            (((binary >> 20) & 0x1) << 11) | 
            (((binary >> 21) & 0x3FF) << 1) |  
            (((binary >> 31) & 0x1) << 20);
}
void InstructionUJ::execute(Memory& memory, RegBank<uint32_t>& regbank, uint32_t& pc)
{
    switch (m_opcode) // DUVIDA SE JALR DEVERIA ESTAR AQUI
    {
    case (kJALCode):
        regbank[m_rd] = pc + 4;
        pc += m_imm;
        break;
    default:
        break;
    }
}