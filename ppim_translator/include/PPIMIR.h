#ifndef PPIMIR_H
#define PPIMIR_H

#include <cstdint>
#include <vector>

// Define our IR structure
struct PPIMIR {
    enum OpType {
        NOOP = 0,  // 00
        PROG = 1,  // 01
        EXE = 2,   // 10
        END = 3    // 11
    };
    
    enum OpCode {
        LDB, // Load buffer
        OUT, // Write accumulator to I/O buffer
        STB, // Store buffer to memory
        PRG, // Program LUT-core
        MAC, // Multiply and Accumulate
        RLU, // ReLU Activation
        MPL  // Max-pooling
    };
    
    struct Instruction {
        OpType type;
        uint8_t pointer;
        bool readBit;
        bool writeBit;
        uint16_t rowAddress;
        OpCode opcode; // For EXE instructions
    };
};

#endif // PPIMIR_H
