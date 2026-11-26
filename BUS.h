#include <cstdint>

class BUS
{
    uint8_t cpuRam[2048];

public:
    BUS();

    uint8_t Read(uint16_t addr);

    void Write(uint16_t addr, uint8_t data);
};
