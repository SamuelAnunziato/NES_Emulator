#include <iostream>
#include <cstdint>

#include "CPU.h"
#include "BUS.h"

// g++ -std=c++17 -Wall -Wextra -O2 main.cpp CPU.cpp BUS.cpp -o emulator
// ./emulator

int main()
{
    CPU cpu;
    BUS bus;
    cpu.bus = &bus;

    return 0;
}
