#include <vector>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include "cpu.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        puts("Usage: crvemu <filename>");
        return -1;
    }

    FILE *fptr;
    fptr = fopen(argv[1], "rb");

    if (fptr == NULL) {
        puts("File does not exist.");
        return -1;
    }

    // Copy code from file to vector
    std::vector<uint8_t> binary;
    uint8_t byte;
    while(fread(&byte, sizeof(byte), 1, fptr) != 0) {
        binary.push_back(byte);
    }

    fclose(fptr);
    Cpu cpu(binary);

    // Fetch-decode-execute
    uint32_t inst;
    do {
        inst = cpu.fetch();
        cpu.execute(inst);
        cpu.dump();
    } while(inst != 0);
    
    return 0;
}
