#include "CPU.h"
#include "BUS.h"

CPU::CPU()
{
    const INSTRUCTION default_instruction{
        "???",
        &CPU::XXX,
        &CPU::IMP,
        2};
    search_opcode.fill(default_instruction);

    search_opcode[0x61] = {"ADC", &CPU::ADC, &CPU::IDX, 6};
    search_opcode[0x65] = {"ADC", &CPU::ADC, &CPU::ZP0, 3};
    search_opcode[0x69] = {"ADC", &CPU::ADC, &CPU::IMM, 2};
    search_opcode[0x6D] = {"ADC", &CPU::ADC, &CPU::ABS, 4};
    search_opcode[0x71] = {"ADC", &CPU::ADC, &CPU::IDY, 5};
    search_opcode[0x75] = {"ADC", &CPU::ADC, &CPU::ZPX, 4};
    search_opcode[0x79] = {"ADC", &CPU::ADC, &CPU::ABY, 4};
    search_opcode[0x7D] = {"ADC", &CPU::ADC, &CPU::ABX, 4};

    search_opcode[0x21] = {"AND", &CPU::AND, &CPU::IDX, 6};
    search_opcode[0x25] = {"AND", &CPU::AND, &CPU::ZP0, 3};
    search_opcode[0x29] = {"AND", &CPU::AND, &CPU::IMM, 2};
    search_opcode[0x2D] = {"AND", &CPU::AND, &CPU::ABS, 4};
    search_opcode[0x31] = {"AND", &CPU::AND, &CPU::IDY, 5};
    search_opcode[0x35] = {"AND", &CPU::AND, &CPU::ZPX, 4};
    search_opcode[0x39] = {"AND", &CPU::AND, &CPU::ABY, 4};
    search_opcode[0x3D] = {"AND", &CPU::AND, &CPU::ABX, 4};

    search_opcode[0x06] = {"ASL", &CPU::ASL, &CPU::ZP0, 5};
    search_opcode[0x0A] = {"ASL", &CPU::ASL, &CPU::ACC, 2};
    search_opcode[0x0E] = {"ASL", &CPU::ASL, &CPU::ABS, 6};
    search_opcode[0x16] = {"ASL", &CPU::ASL, &CPU::ZPX, 6};
    search_opcode[0x1E] = {"ASL", &CPU::ASL, &CPU::ABX, 7};

    search_opcode[0x90] = {"BCC", &CPU::BCC, &CPU::REL, 2};

    search_opcode[0xB0] = {"BCS", &CPU::BCS, &CPU::REL, 2};

    search_opcode[0xF0] = {"BEQ", &CPU::BEQ, &CPU::REL, 2};

    search_opcode[0x24] = {"BIT", &CPU::BIT, &CPU::ZP0, 3};
    search_opcode[0x2C] = {"BIT", &CPU::BIT, &CPU::ABS, 4};

    search_opcode[0x30] = {"BMI", &CPU::BMI, &CPU::REL, 2};

    search_opcode[0xD0] = {"BNE", &CPU::BNE, &CPU::REL, 2};

    search_opcode[0x10] = {"BPL", &CPU::BPL, &CPU::REL, 2};

    search_opcode[0x00] = {"BRK", &CPU::BRK, &CPU::IMM, 7};

    search_opcode[0x50] = {"BVC", &CPU::BVC, &CPU::REL, 2};

    search_opcode[0x70] = {"BVS", &CPU::BVS, &CPU::REL, 2};

    search_opcode[0x18] = {"CLC", &CPU::CLC, &CPU::IMP, 2};

    search_opcode[0xD8] = {"CLD", &CPU::CLD, &CPU::IMP, 2};

    search_opcode[0x58] = {"CLI", &CPU::CLI, &CPU::IMP, 2};

    search_opcode[0xB8] = {"CLV", &CPU::CLV, &CPU::IMP, 2};

    search_opcode[0xC1] = {"CMP", &CPU::CMP, &CPU::IDX, 6};
    search_opcode[0xC5] = {"CMP", &CPU::CMP, &CPU::ZP0, 3};
    search_opcode[0xC9] = {"CMP", &CPU::CMP, &CPU::IMM, 2};
    search_opcode[0xCD] = {"CMP", &CPU::CMP, &CPU::ABS, 4};
    search_opcode[0xD1] = {"CMP", &CPU::CMP, &CPU::IDY, 5};
    search_opcode[0xD5] = {"CMP", &CPU::CMP, &CPU::ZPX, 4};
    search_opcode[0xD9] = {"CMP", &CPU::CMP, &CPU::ABY, 4};
    search_opcode[0xDD] = {"CMP", &CPU::CMP, &CPU::ABX, 4};

    search_opcode[0xE0] = {"CPX", &CPU::CPX, &CPU::IMM, 2};
    search_opcode[0xE4] = {"CPX", &CPU::CPX, &CPU::ZP0, 3};
    search_opcode[0xEC] = {"CPX", &CPU::CPX, &CPU::ABS, 4};

    search_opcode[0xC0] = {"CPY", &CPU::CPY, &CPU::IMM, 2};
    search_opcode[0xC4] = {"CPY", &CPU::CPY, &CPU::ZP0, 3};
    search_opcode[0xCC] = {"CPY", &CPU::CPY, &CPU::ABS, 4};

    search_opcode[0xC6] = {"DEC", &CPU::DEC, &CPU::ZP0, 5};
    search_opcode[0xCE] = {"DEC", &CPU::DEC, &CPU::ABS, 6};
    search_opcode[0xD6] = {"DEC", &CPU::DEC, &CPU::ZPX, 6};
    search_opcode[0xDE] = {"DEC", &CPU::DEC, &CPU::ABX, 7};

    search_opcode[0xCA] = {"DEX", &CPU::DEX, &CPU::IMP, 2};

    search_opcode[0x88] = {"DEY", &CPU::DEY, &CPU::IMP, 2};

    search_opcode[0x41] = {"EOR", &CPU::EOR, &CPU::IDX, 6};
    search_opcode[0x45] = {"EOR", &CPU::EOR, &CPU::ZP0, 3};
    search_opcode[0x49] = {"EOR", &CPU::EOR, &CPU::IMM, 2};
    search_opcode[0x4D] = {"EOR", &CPU::EOR, &CPU::ABS, 4};
    search_opcode[0x51] = {"EOR", &CPU::EOR, &CPU::IDY, 5};
    search_opcode[0x55] = {"EOR", &CPU::EOR, &CPU::ZPX, 4};
    search_opcode[0x59] = {"EOR", &CPU::EOR, &CPU::ABY, 4};
    search_opcode[0x5D] = {"EOR", &CPU::EOR, &CPU::ABX, 4};

    search_opcode[0xE6] = {"INC", &CPU::INC, &CPU::ZP0, 5};
    search_opcode[0xEE] = {"INC", &CPU::INC, &CPU::ABS, 6};
    search_opcode[0xF6] = {"INC", &CPU::INC, &CPU::ZPX, 6};
    search_opcode[0xFE] = {"INC", &CPU::INC, &CPU::ABX, 7};

    search_opcode[0xE8] = {"INX", &CPU::INX, &CPU::IMP, 2};

    search_opcode[0xC8] = {"INY", &CPU::INY, &CPU::IMP, 2};

    search_opcode[0x4C] = {"JMP", &CPU::JMP, &CPU::ABS, 3};
    search_opcode[0x6C] = {"JMP", &CPU::JMP, &CPU::IND, 5};

    search_opcode[0x20] = {"JSR", &CPU::JSR, &CPU::ABS, 6};

    search_opcode[0xA1] = {"LDA", &CPU::LDA, &CPU::IDX, 6};
    search_opcode[0xA5] = {"LDA", &CPU::LDA, &CPU::ZP0, 3};
    search_opcode[0xA9] = {"LDA", &CPU::LDA, &CPU::IMM, 2};
    search_opcode[0xAD] = {"LDA", &CPU::LDA, &CPU::ABS, 4};
    search_opcode[0xB1] = {"LDA", &CPU::LDA, &CPU::IDY, 5};
    search_opcode[0xB5] = {"LDA", &CPU::LDA, &CPU::ZPX, 4};
    search_opcode[0xB9] = {"LDA", &CPU::LDA, &CPU::ABY, 4};
    search_opcode[0xBD] = {"LDA", &CPU::LDA, &CPU::ABX, 4};

    search_opcode[0xA2] = {"LDX", &CPU::LDX, &CPU::IMM, 2};
    search_opcode[0xA6] = {"LDX", &CPU::LDX, &CPU::ZP0, 3};
    search_opcode[0xAE] = {"LDX", &CPU::LDX, &CPU::ABS, 4};
    search_opcode[0xB6] = {"LDX", &CPU::LDX, &CPU::ZPY, 4};
    search_opcode[0xBE] = {"LDX", &CPU::LDX, &CPU::ABY, 4};

    search_opcode[0xA0] = {"LDY", &CPU::LDY, &CPU::IMM, 2};
    search_opcode[0xA4] = {"LDY", &CPU::LDY, &CPU::ZP0, 3};
    search_opcode[0xAC] = {"LDY", &CPU::LDY, &CPU::ABS, 4};
    search_opcode[0xB4] = {"LDY", &CPU::LDY, &CPU::ZPX, 4};
    search_opcode[0xBC] = {"LDY", &CPU::LDY, &CPU::ABX, 4};

    search_opcode[0x46] = {"LSR", &CPU::LSR, &CPU::ZP0, 5};
    search_opcode[0x4A] = {"LSR", &CPU::LSR, &CPU::ACC, 2};
    search_opcode[0x4E] = {"LSR", &CPU::LSR, &CPU::ABS, 6};
    search_opcode[0x56] = {"LSR", &CPU::LSR, &CPU::ZPX, 6};
    search_opcode[0x5E] = {"LSR", &CPU::LSR, &CPU::ABX, 7};

    search_opcode[0x1A] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    search_opcode[0x3A] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    search_opcode[0x5A] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    search_opcode[0x7A] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    search_opcode[0xDA] = {"NOP", &CPU::NOP, &CPU::IMP, 2};
    search_opcode[0xEA] = {"NOP", &CPU::NOP, &CPU::IMP, 2}; // official opcode
    search_opcode[0xFA] = {"NOP", &CPU::NOP, &CPU::IMP, 2};

    search_opcode[0x01] = {"ORA", &CPU::ORA, &CPU::IDX, 6};
    search_opcode[0x05] = {"ORA", &CPU::ORA, &CPU::ZP0, 3};
    search_opcode[0x09] = {"ORA", &CPU::ORA, &CPU::IMM, 2};
    search_opcode[0x0D] = {"ORA", &CPU::ORA, &CPU::ABS, 4};
    search_opcode[0x11] = {"ORA", &CPU::ORA, &CPU::IDY, 5};
    search_opcode[0x15] = {"ORA", &CPU::ORA, &CPU::ZPX, 4};
    search_opcode[0x19] = {"ORA", &CPU::ORA, &CPU::ABY, 4};
    search_opcode[0x1D] = {"ORA", &CPU::ORA, &CPU::ABX, 4};

    search_opcode[0x48] = {"PHA", &CPU::PHA, &CPU::IMP, 3};

    search_opcode[0x08] = {"PHP", &CPU::PHP, &CPU::IMP, 3};

    search_opcode[0x68] = {"PLA", &CPU::PLA, &CPU::IMP, 4};

    search_opcode[0x28] = {"PLP", &CPU::PLP, &CPU::IMP, 4};

    search_opcode[0x26] = {"ROL", &CPU::ROL, &CPU::ZP0, 5};
    search_opcode[0x2A] = {"ROL", &CPU::ROL, &CPU::ACC, 2};
    search_opcode[0x2E] = {"ROL", &CPU::ROL, &CPU::ABS, 6};
    search_opcode[0x36] = {"ROL", &CPU::ROL, &CPU::ZPX, 6};
    search_opcode[0x3E] = {"ROL", &CPU::ROL, &CPU::ABX, 7};

    search_opcode[0x66] = {"ROR", &CPU::ROR, &CPU::ZP0, 5};
    search_opcode[0x6A] = {"ROR", &CPU::ROR, &CPU::ACC, 2};
    search_opcode[0x6E] = {"ROR", &CPU::ROR, &CPU::ABS, 6};
    search_opcode[0x76] = {"ROR", &CPU::ROR, &CPU::ZPX, 6};
    search_opcode[0x7E] = {"ROR", &CPU::ROR, &CPU::ABX, 7};

    search_opcode[0x40] = {"RTI", &CPU::RTI, &CPU::IMP, 6};

    search_opcode[0x60] = {"RTS", &CPU::RTS, &CPU::IMP, 6};

    search_opcode[0xE1] = {"SBC", &CPU::SBC, &CPU::IDX, 6};
    search_opcode[0xE5] = {"SBC", &CPU::SBC, &CPU::ZP0, 3};
    search_opcode[0xE9] = {"SBC", &CPU::SBC, &CPU::IMM, 2};
    search_opcode[0xED] = {"SBC", &CPU::SBC, &CPU::ABS, 4};
    search_opcode[0xF1] = {"SBC", &CPU::SBC, &CPU::IDY, 5};
    search_opcode[0xF5] = {"SBC", &CPU::SBC, &CPU::ZPX, 4};
    search_opcode[0xF9] = {"SBC", &CPU::SBC, &CPU::ABY, 4};
    search_opcode[0xFD] = {"SBC", &CPU::SBC, &CPU::ABX, 4};

    search_opcode[0x38] = {"SEC", &CPU::SEC, &CPU::IMP, 2};

    search_opcode[0xF8] = {"SED", &CPU::SED, &CPU::IMP, 2};

    search_opcode[0x78] = {"SEI", &CPU::SEI, &CPU::IMP, 2};

    search_opcode[0x81] = {"STA", &CPU::STA, &CPU::IDX, 6};
    search_opcode[0x85] = {"STA", &CPU::STA, &CPU::ZP0, 3};
    search_opcode[0x8D] = {"STA", &CPU::STA, &CPU::ABS, 4};
    search_opcode[0x91] = {"STA", &CPU::STA, &CPU::IDY, 6};
    search_opcode[0x95] = {"STA", &CPU::STA, &CPU::ZPX, 4};
    search_opcode[0x99] = {"STA", &CPU::STA, &CPU::ABY, 5};
    search_opcode[0x9D] = {"STA", &CPU::STA, &CPU::ABX, 5};

    search_opcode[0x86] = {"STX", &CPU::STX, &CPU::ZP0, 3};
    search_opcode[0x8E] = {"STX", &CPU::STX, &CPU::ABS, 4};
    search_opcode[0x96] = {"STX", &CPU::STX, &CPU::ZPY, 4};

    search_opcode[0x84] = {"STY", &CPU::STY, &CPU::ZP0, 3};
    search_opcode[0x8C] = {"STY", &CPU::STY, &CPU::ABS, 4};
    search_opcode[0x94] = {"STY", &CPU::STY, &CPU::ZPX, 4};

    search_opcode[0xAA] = {"TAX", &CPU::TAX, &CPU::IMP, 2};

    search_opcode[0xA8] = {"TAY", &CPU::TAY, &CPU::IMP, 2};

    search_opcode[0xBA] = {"TSX", &CPU::TSX, &CPU::IMP, 2};

    search_opcode[0x8A] = {"TXA", &CPU::TXA, &CPU::IMP, 2};

    search_opcode[0x9A] = {"TXS", &CPU::TXS, &CPU::IMP, 2};

    search_opcode[0x98] = {"TYA", &CPU::TYA, &CPU::IMP, 2};
}

uint8_t CPU::Read(uint16_t addr)
{
    return bus->Read(addr);
}

void CPU::Read_Word(uint16_t addr)
{
    word = bus->Read(addr);
}

void CPU::Write(uint16_t addr, uint8_t data)
{
    bus->Write(addr, data);
}

uint8_t CPU::GetFlag(CPU::FLAGS flag)
{
    uint8_t nf = 0x00 | static_cast<uint8_t>(flag);
    return (status & nf) > 0 ? 1 : 0;
}

void CPU::SetFlag(CPU::FLAGS flag, bool b)
{
    uint8_t nf = 0x00 | static_cast<uint8_t>(flag);
    if (b)
    {
        status |= nf;
    }
    else
    {
        status &= ~nf;
    }
}

void CPU::Reset()
{
    a = 0x00;
    x = 0x00;
    y = 0x00;

    sp = 0xFD;

    status = 0x00;
    SetFlag(I, 1);
    SetFlag(U, 1);

    pc = Read(0xFFFC);
    pc |= (Read(0xFFFD) << 8);

    adl = 0x00;
    adh = 0x00;

    word = 0x00;

    cycles = 7;
}

void CPU::IRQ()
{
    if (!GetFlag(I))
    {
        Write(0x0100 + sp, (pc >> 8));
        sp--;
        Write(0x0100 + sp, pc);
        sp--;
        SetFlag(I, 1);
        Write(0x0100 + sp, status);
        sp--;

        pc = Read(0xFFFE);
        pc |= (Read(0xFFFF) << 8);

        cycles = 7;
    }
}

void CPU::NMI()
{
    Write(0x0100 + sp, (pc >> 8));
    sp--;
    Write(0x0100 + sp, pc);
    sp--;
    SetFlag(I, 1);
    Write(0x0100 + sp, status);
    sp--;

    pc = Read(0xFFFA);
    pc |= (Read(0xFFFB) << 8);

    cycles = 7;
}

void CPU::XXX()
{
    printf(
        "OPCODE NAO IMPLEMENTADO: PC=%04X OP=%02X\n",
        pc,
        Read(pc));
}

void CPU::ACC()
{
    word = a;
}

void CPU::IMP() {}

void CPU::IMM()
{
    Read_Word(pc);
    pc++;
}

void CPU::ABS()
{
    adl = Read(pc);
    pc++;

    adh = Read(pc);
    pc++;

    Read_Word((adh << 8) | adl);
}

void CPU::ABX()
{
    uint16_t sum = 0x0000;

    adl = Read(pc);
    pc++;

    sum = adl + x;
    adl = sum;
    adh = Read(pc);
    pc++;

    if ((sum >> 8) != 0)
    {
        adh += sum >> 8;
        cycles++;
    }

    Read_Word((adh << 8) | adl);
}

void CPU::ABY()
{
    uint16_t sum = 0x0000;

    adl = Read(pc);
    pc++;

    sum = adl + y;
    adl = sum;
    adh = Read(pc);
    pc++;

    if ((sum >> 8) != 0)
    {
        adh += sum >> 8;
        cycles++;
    }

    Read_Word((adh << 8) | adl);
}

void CPU::ZP0()
{
    adl = Read(pc);
    adh = 0x00;
    pc++;

    Read_Word((adh << 8) | adl);
}

void CPU::ZPX()
{
    adl = Read(pc);
    adh = 0x00;
    pc++;

    adl += x;

    Read_Word((adh << 8) | adl);
}

void CPU::ZPY()
{
    adl = Read(pc);
    adh = 0x00;
    pc++;

    adl += y;

    Read_Word((adh << 8) | adl);
}

void CPU::REL()
{
    word = Read(pc);
    pc++;
}

void CPU::IND()
{
    uint8_t bal = 0x00;
    uint8_t bah = 0x00;

    bal = Read(pc);
    pc++;

    bah = Read(pc);
    pc++;

    adl = Read((bah << 8) | bal);
    bal++;

    adh = Read((bah << 8) | bal);
}

void CPU::IDX()
{
    uint8_t bal = 0x00;

    bal = Read(pc);
    pc++;

    bal += x;

    adl = Read((0x00 << 8) | bal);
    bal++;

    adh = Read((0x00 << 8) | bal);

    Read_Word((adh << 8) | adl);
}

void CPU::IDY()
{
    uint8_t bal = 0x00;
    uint16_t sum = 0x0000;

    bal = Read(pc);
    pc++;

    adl = Read((0x00 << 8) | bal);
    bal++;

    sum = adl + y;
    adl = sum;
    adh = Read((0x00 << 8) | bal);

    if ((sum >> 8) != 0)
    {
        adh += sum >> 8;
        cycles++;
    }

    Read_Word((adh << 8) | adl);
}

void CPU::ADC()
{
    uint16_t result = a + word + GetFlag(C);

    SetFlag(C, result & 0x0100);
    SetFlag(Z, (result & 0x00FF) == 0);
    SetFlag(V, (result ^ a) & (result ^ word) & 0x80);
    SetFlag(N, result & 0x80);

    a = result;
}

void CPU::AND()
{
    a &= word;

    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);
}

void CPU::ASL()
{
    uint16_t result = word << 1;

    SetFlag(C, word & 0x100);
    SetFlag(Z, (result & 0x0FF) == 0);
    SetFlag(N, result & 0x80);

    if (search_opcode[opcode].addrmode == &CPU::ACC)
    {
        a = result;
    }
    else
    {
        Write((adh << 8) | adl, result);
    }
}

void CPU::BCC()
{
    if (!GetFlag(C))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::BCS()
{
    if (GetFlag(C))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::BEQ()
{
    if (GetFlag(Z))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::BIT()
{
    uint8_t result = a & word;

    SetFlag(Z, result == 0);
    SetFlag(V, word & 0x70);
    SetFlag(N, word & 0x80);
}

void CPU::BMI()
{
    if (GetFlag(N))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::BNE()
{
    if (!GetFlag(Z))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::BPL()
{
    if (!GetFlag(N))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::BRK()
{
    pc++;

    SetFlag(I, 1);
    Write(0x0100 + sp, (pc >> 8));
    sp--;
    Write(0x0100 + sp, pc);
    sp--;
    Write(0x0100 + sp, (status | B));
    sp--;

    pc = Read(0xFFFE);
    pc |= (Read(0xFFFF) << 8);
}

void CPU::BVC()
{
    if (!GetFlag(V))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::BVS()
{
    if (GetFlag(V))
    {
        int8_t offset = static_cast<int8_t>(word);
        uint16_t oldPC = pc;

        pc += offset;

        cycles++;
        if ((oldPC & 0xFF00) != (pc & 0xFF00))
            cycles++;
    }
}

void CPU::CLC()
{
    SetFlag(C, 0);
}

void CPU::CLD()
{
    SetFlag(D, 0);
}

void CPU::CLI()
{
    SetFlag(I, 0);
}

void CPU::CLV()
{
    SetFlag(V, 0);
}

void CPU::CMP()
{
    uint8_t result = a - word;

    SetFlag(C, a >= word);
    SetFlag(Z, result == 0);
    SetFlag(N, result & 0x80);
}

void CPU::CPX()
{
    uint8_t result = x - word;

    SetFlag(C, x >= word);
    SetFlag(Z, result == 0);
    SetFlag(N, result & 0x80);
}

void CPU::CPY()
{
    uint8_t result = y - word;

    SetFlag(C, y >= word);
    SetFlag(Z, (result & 0xFF) == 0);
    SetFlag(N, result & 0x80);
}

void CPU::DEC()
{
    uint8_t result = word - 1;
    Write((adh << 8) | adl, result);

    SetFlag(Z, result == 0);
    SetFlag(N, result & 0x80);
}

void CPU::DEX()
{
    x--;

    SetFlag(Z, x == 0);
    SetFlag(N, x & 0x80);
}

void CPU::DEY()
{
    y--;

    SetFlag(Z, y == 0);
    SetFlag(N, y & 0x80);
}

void CPU::EOR()
{
    a = a ^ word;

    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);
}

void CPU::INC()
{
    uint8_t result = word + 1;
    Write((adh << 8) | adl, result);

    SetFlag(Z, result == 0);
    SetFlag(N, result & 0x80);
}

void CPU::INX()
{
    x++;

    SetFlag(Z, x == 0);
    SetFlag(N, x & 0x80);
}

void CPU::INY()
{
    y++;

    SetFlag(Z, y == 0);
    SetFlag(N, y & 0x80);
}

void CPU::JMP()
{
    pc = (adh << 8) | adl;
}

void CPU::JSR()
{
    uint16_t return_address = pc - 1;

    Write(0x0100 + sp, (return_address >> 8));
    sp--;
    Write(0x0100 + sp, return_address);
    sp--;

    pc = (adh << 8) | adl;
}

void CPU::LDA()
{
    a = word;

    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);
}

void CPU::LDX()
{
    x = word;

    SetFlag(Z, x == 0);
    SetFlag(N, x & 0x80);
}

void CPU::LDY()
{
    y = word;

    SetFlag(Z, y == 0);
    SetFlag(N, y & 0x80);
}

void CPU::LSR()
{
    uint8_t result = word >> 1;

    SetFlag(C, word & 0x01);
    SetFlag(Z, result == 0);
    SetFlag(N, 0);

    if (search_opcode[opcode].addrmode == &CPU::ACC)
    {
        a = result;
    }
    else
    {
        Write((adh << 8) | adl, result);
    }
}

void CPU::NOP() {}

void CPU::ORA()
{
    a |= word;

    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);
}

void CPU::PHA()
{
    Write(0x0100 + sp, a);
    sp--;
}

void CPU::PHP()
{
    Write(0x0100 + sp, status | B | U);
    sp--;
}

void CPU::PLA()
{
    sp++;
    a = Read(0x0100 + sp);

    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);
}

void CPU::PLP()
{
    sp++;
    status = Read(0x0100 + sp);

    SetFlag(U, 1);
    SetFlag(B, 0);
}

void CPU::ROL()
{
    uint8_t result = (word << 1) & GetFlag(C);

    SetFlag(C, word & 0x80);
    SetFlag(Z, result == 0);
    SetFlag(N, result & 0x80);

    if (search_opcode[opcode].addrmode == &CPU::ACC)
    {
        a = result;
    }
    else
    {
        Write((adh << 8) | adl, result);
    }
}

void CPU::ROR()
{
    uint8_t result = (word >> 1) & (GetFlag(C) << 7);

    SetFlag(C, word & 0x01);
    SetFlag(Z, result == 0);
    SetFlag(N, result & 0x80);

    if (search_opcode[opcode].addrmode == &CPU::ACC)
    {
        a = result;
    }
    else
    {
        Write((adh << 8) | adl, result);
    }
}

void CPU::RTI()
{
    sp++;
    status = Read(0x0100 + sp);
    sp++;
    pc = Read(0x0100 + sp);
    sp++;
    pc |= (Read(0x0100 + sp) << 8);

    SetFlag(B, 0);
    SetFlag(U, 1);
}

void CPU::RTS()
{
    sp++;
    pc = Read(0x0100 + sp);
    sp++;
    pc |= (Read(0x0100 + sp) << 8);
    pc++;
}

void CPU::SBC()
{
    uint16_t result = a - word - ~GetFlag(C);

    SetFlag(C, result & 0x0100);
    SetFlag(Z, (result & 0x00FF) == 0);
    SetFlag(V, (result ^ a) & (result ^ ~word) & 0x80);
    SetFlag(N, result & 0x80);

    a = result;
}

void CPU::SEC()
{
    SetFlag(C, 1);
}

void CPU::SED()
{
    SetFlag(D, 1);
}

void CPU::SEI()
{
    SetFlag(I, 1);
}

void CPU::STA()
{
    Write((adh << 8) | adl, a);
}

void CPU::STX()
{
    Write((adh << 8) | adl, x);
}

void CPU::STY()
{
    Write((adh << 8) | adl, y);
}

void CPU::TAX()
{
    x = a;

    SetFlag(Z, x == 0);
    SetFlag(N, x & 0x80);
}

void CPU::TAY()
{
    y = a;

    SetFlag(Z, y == 0);
    SetFlag(N, y & 0x80);
}

void CPU::TSX()
{
    x = sp;

    SetFlag(Z, x == 0);
    SetFlag(N, x & 0x80);
}

void CPU::TXA()
{
    a = x;

    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);
}

void CPU::TXS()
{
    sp = x;
}

void CPU::TYA()
{
    a = y;

    SetFlag(Z, a == 0);
    SetFlag(N, a & 0x80);
}

void CPU::Execute()
{
    if (cycles == 0)
    {
        opcode = Read(pc);
        pc++;

        cycles = search_opcode[opcode].cycles;
        (this->*search_opcode[opcode].addrmode)();
        (this->*search_opcode[opcode].operation)();
    }
    cycles--;
}
