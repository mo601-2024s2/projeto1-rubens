#include <RiscV.hpp>

void RiscV::run() {

        
    m_binary = this->m_memory.read(this->m_pc * 4);

    while(m_binary != 0x0) {
        m_binary = this->m_memory.read(this->m_pc * 4);
        this->fetch();
        m_pc += 1;  // Increase the PC (program counter)
    }
}

void RiscV::fetch()
{
    uint8_t opcode = m_binary & 0x7F;
    switch (opcode)
    {
    case RTypeOpCode:
        this->m_instruction = new InstructionR();
        break;
    case IType1OpCode:
    case IType2OpCode:
        this->m_instruction = new InstructionI();
        break;
    case STypeOpCode:
        this->m_instruction = new InstructionS();
        break;
    case BTypeOpCode:
        this->m_instruction = new InstructionSB();
        break;
    case UType1OpCode:
    case UType2OpCode:
        this->m_instruction = new InstructionU();
        break;
    case JTypeOpCode:
        this->m_instruction = new InstructionUJ();
         break;    
    default:
        break;
    }

    std::cout << "pc: " << m_pc << std::endl; // To delete
    this->m_instruction->decode(m_binary);


}

void RiscV::execute()
{
    m_instruction->execute(m_memory, m_regbank, m_pc);
}
