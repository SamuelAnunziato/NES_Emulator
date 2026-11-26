#include <cstdint>
#include <array>
#include <iostream>

class BUS;

class CPU
{
public:
    CPU();

//private:
    uint8_t a      = 0x00;      // accumulator
    uint8_t x      = 0x00;      // index X
    uint8_t y      = 0x00;      // index Y
    uint8_t sp     = 0x00;      // stack pointer
    uint8_t status = 0x00;      // 7 flags
    uint16_t pc    = 0x0000;    // program counter

    uint8_t adl = 0x00;     // acts as both an ADL latch and an ABL latch
    uint8_t adh = 0x00;     // acts as both an ADH latch and an ABH latch

    uint8_t opcode = 0x00;

    struct INSTRUCTION
    {
        const char* name;                   // instruction name
        void    (CPU::*operation)(void);    // does not affect the cycles directly
        void    (CPU::*addrmode)(void);     // returns possible extra cycles
        uint8_t cycles = 0;                 // base cycles
    };
    std::array<INSTRUCTION, 256> search_opcode; // contains all the opcodes

    // addressing modes: 13 in total
    void ACC(); void IMP(); void IMM(); void ABS();
    void ABX(); void ABY(); void ZP0(); void ZPY();
    void ZPX(); void REL(); void IND(); void IDX();
    void IDY(); void XXX();

    // opcodes: 56 in total
    void ADC(); void AND(); void ASL(); void BCC();
    void BCS(); void BEQ(); void BIT(); void BMI();
    void BNE(); void BPL(); void BRK(); void BVC();
    void BVS(); void CLC(); void CLD(); void CLI();
    void CLV(); void CMP(); void CPX(); void CPY();
    void DEC(); void DEX(); void DEY(); void EOR();
    void INC(); void INX(); void INY(); void JMP();
    void JSR(); void LDA(); void LDX(); void LDY();
    void LSR(); void NOP(); void ORA(); void PHA();
    void PHP(); void PLA(); void PLP(); void ROL();
    void ROR(); void RTI(); void RTS(); void SBC();
    void SEC(); void SED(); void SEI(); void STA();
    void STX(); void STY(); void TAX(); void TAY();
    void TSX(); void TXA(); void TXS(); void TYA();

    BUS     *bus = nullptr;
    uint8_t word = 0x00; // variable used to store the word read from memory, for cases where the variable to be defined is uncertain

    uint8_t Read(uint16_t addr);      // reads from memory and returns the value
    void    Read_Word(uint16_t addr); // reads from memory and set the variable word
    void    Write(uint16_t addr, uint8_t data);

    enum FLAGS
    {
        C = (1 << 0),   // carry bit
        Z = (1 << 1),   // zero
        I = (1 << 2),   // disable interrupts
        D = (1 << 3),   // decimal mode
        B = (1 << 4),   // break
        U = (1 << 5),   // unused
        V = (1 << 6),   // overflow
        N = (1 << 7),   // negative
    };

    uint8_t GetFlag(FLAGS flag);
    void SetFlag(FLAGS flag, bool b);

    void Reset();
    void IRQ();
    void NMI();

    void Execute();

public:
    uint8_t  cycles     = 0;   // counts how many cycles the instruction has remaining
    uint32_t clocks     = 0;   // cpu count of clocks
};
