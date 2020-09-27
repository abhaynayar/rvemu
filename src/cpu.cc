#include <cstdio>
#include <cstring>
#include <cstdint>
#include "cpu.h"

// Fetch an instruction from memory
uint32_t Cpu::fetch() {
    uint32_t inst = mem[pc]
        | mem[pc+1] << 8
        | mem[pc+2] << 16
        | mem[pc+3] << 24;

    pc += 4;
    return inst;
}

// Initalize the cpu
Cpu::Cpu(char* fname) {
    
    pc = 0; // Instructions start at this address
    memset(reg, 0, 32*sizeof(uint64_t));
    reg[0] = 0; // Hardwired to zero
    reg[2] = MEMSIZE; // Stack pointer
    
    FILE *fptr;
    fptr = fopen(fname, "rb");

    if (fptr == NULL) {
        puts("File does not exist.");
        return;
    }

    // Copy code from file to memory
    memset(mem, 0, MEMSIZE*sizeof(uint8_t));
    
    int i=0;
    uint8_t byte;
    while(fread(&byte, sizeof(byte), 1, fptr) != 0) {
        mem[i++] = byte;
    }

    fclose(fptr);
    return;
}

// Execute given instructions on the cpu
void Cpu::execute(uint32_t inst) {

    int opcode = inst & 0x0000007f;
    int rd = (inst & 0x00000f80) >> 7;
    int rs1 = (inst & 0x000f8000) >> 15;
    int rs2 = (inst & 0x01f00000) >> 20;
    int funct3 = (inst & 0x00007000) >> 12;
    int funct7 = (inst & 0xfe000000) >> 25;

    switch (opcode) {

        // addi
        case 0x13: {
            // TODO: check if type casting works as intended
            uint64_t imm = (int64_t)((int32_t)(inst&0xfff00000)) >> 20;
            reg[rd] = reg[rs1] + imm;
            break;
        }

        // add
        case 0x33: {
            // TODO: check if this is a wrapping add
            reg[rd] = reg[rs1] + reg[rs2];
            break;
        }

        // Branch instructions
        case 0x63: {
            // imm[12|10:5|4:1|11] = inst[31|30:25|11:8|7]
            uint64_t imm = (int64_t)((int32_t)(inst & 0x80000000)) >> 19
                | ((inst & 0x80) << 4)   // imm[11]
                | ((inst >> 20) & 0x7e0) // imm[10:5]
                | ((inst >> 7) & 0x1e);  // imm[4:1]
            
            switch(funct3) {
                // ...
            }
        }
        
        default: {
            printf("opcode %x not implemented yet", opcode);
            return;
        }
    }

    return;
}

// Dump program counter and registers
void Cpu::dump() {
    const char* abi[] = {
            "zero", " ra ", " sp ", " gp ", " tp ", " t0 ", " t1 ",
            " t2 ", " s0 ", " s1 ", " a0 ", " a1 ", " a2 ", " a3 ",
            " a4 ", " a5 ", " a6 ", " a7 ", " s2 ", " s3 ", " s4 ",
            " s5 ", " s6 ", " s7 ", " s8 ", " s9 ", " s10", " s11",
            " t3 ", " t4 ", " t5 ", " t6 "
    };
    
    printf("pc:\t\t%lx\n", pc);
    for (int i=0; i<32; ++i) {
        printf("x%02d(%s)\t%lx\n", i, abi[i], reg[i]);
    }

    puts("\n");
    return;
}

