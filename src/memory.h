#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#define MEMORY_BASE 0x80000000
#define MEMORY_SIZE 1024*1024*128 // 128 MiB

#include <vector>
#include <cstdint>

class Memory {
    std::vector<uint8_t> memory;

public:

    Memory(std::vector<uint8_t> binary);
    uint64_t load(uint64_t addr, uint64_t size);
    uint64_t load8(uint64_t addr);
    uint64_t load16(uint64_t addr);
    uint64_t load32(uint64_t addr);
    uint64_t load64(uint64_t addr);

    void store(uint64_t addr, uint64_t size, uint64_t value);
    void store8(uint64_t addr, uint64_t value);
    void store16(uint64_t addr, uint64_t value);
    void store32(uint64_t addr, uint64_t value);
    void store64(uint64_t addr, uint64_t value);
};

#endif
