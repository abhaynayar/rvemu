#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "bus.h"

#define MEMORY_BASE 0x80000000
#define MEMORY_SIZE 1024*1024*128

class Cpu {
    uint64_t pc;
    uint64_t reg[32];
    uint64_t csrs[4096];
    Bus bus;

public:
    Cpu(std::vector<uint8_t> binary);
    uint64_t fetch();
    void execute(uint32_t inst);
    void dump();

    uint64_t load(uint64_t addr, uint64_t size);
    void store(uint64_t addr, uint64_t size, uint64_t value);
};

#endif
