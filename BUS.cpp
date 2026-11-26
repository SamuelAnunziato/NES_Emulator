#include "BUS.h"

BUS::BUS(){}

uint8_t BUS::Read(uint16_t addr)
{
    if (addr <= 0x1FFF)
    {
        return cpuRam[addr] & 0x07FF;
    }
    return 0x00;
}

void BUS::Write(uint16_t addr, uint8_t data)
{
    if (addr <= 0x1FFF)
    {
        cpuRam[addr] = data;
    }
}
