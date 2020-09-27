#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#define MEMSIZE 0x1000

class Cpu {
    uint64_t pc;
    uint64_t reg[32];
    uint8_t mem[MEMSIZE];

public:
    Cpu(char* fname);
    uint32_t fetch();
    void execute(uint32_t inst);
    void dump();

};

#endif
