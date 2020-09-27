#include <cstdio>
#include <cstdint>
#include "cpu.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        puts("Usage: crvemu <filename>");
        return 1;
    }

    Cpu cpu(argv[1]);
    
    // Fetch-decode-execute
    uint32_t inst;
    do {
        inst = cpu.fetch();
        cpu.execute(inst);
        cpu.dump();
    
    } while(inst != 0);
    return 0;
}

