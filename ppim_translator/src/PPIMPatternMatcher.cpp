#include "../include/PPIMPatternMatcher.h"

PPIMIR::Instruction PPIMPatternMatcher::generateLDB(uint16_t memoryRow) {
    PPIMIR::Instruction instr;
    instr.type = PPIMIR::OpType::EXE;
    instr.pointer = PPIMIR::OpCode::LDB;
    instr.readBit = true;
    instr.writeBit = false;
    instr.rowAddress = memoryRow;
    return instr;
}

PPIMIR::Instruction PPIMPatternMatcher::generateOUT(uint16_t bufferLocation) {
    PPIMIR::Instruction instr;
    instr.type = PPIMIR::OpType::EXE;
    instr.pointer = PPIMIR::OpCode::OUT;
    instr.readBit = false;
    instr.writeBit = true;
    instr.rowAddress = bufferLocation;
    return instr;
}

PPIMIR::Instruction PPIMPatternMatcher::generateSTB(uint16_t memoryRow) {
    PPIMIR::Instruction instr;
    instr.type = PPIMIR::OpType::EXE;
    instr.pointer = PPIMIR::OpCode::STB;
    instr.readBit = false;
    instr.writeBit = true;
    instr.rowAddress = memoryRow;
    return instr;
}

PPIMIR::Instruction PPIMPatternMatcher::generatePRG(uint8_t coreID) {
    PPIMIR::Instruction instr;
    instr.type = PPIMIR::OpType::PROG;
    instr.pointer = coreID;
    instr.readBit = true;
    instr.writeBit = false;
    instr.rowAddress = 0;
    return instr;
}

std::vector<PPIMIR::Instruction> PPIMPatternMatcher::generateMAC(uint16_t inputAAddr, uint16_t inputBAddr, uint16_t outputAddr) {
    std::vector<PPIMIR::Instruction> instructions;
    
    // 1. Load first operand
    instructions.push_back(generateLDB(inputAAddr));
    
    // 2. Load second operand
    instructions.push_back(generateLDB(inputBAddr));
    
    // 3. Execute MAC operation
    PPIMIR::Instruction macInstr;
    macInstr.type = PPIMIR::OpType::EXE;
    macInstr.pointer = PPIMIR::OpCode::MAC;
    macInstr.readBit = false;
    macInstr.writeBit = false;
    macInstr.rowAddress = 0;
    instructions.push_back(macInstr);
    
    // 4. Store result
    instructions.push_back(generateSTB(outputAddr));
    
    return instructions;
}

std::vector<PPIMIR::Instruction> PPIMPatternMatcher::generateRLU(uint16_t inputAddr, uint16_t outputAddr) {
    std::vector<PPIMIR::Instruction> instructions;
    
    // 1. Load input
    instructions.push_back(generateLDB(inputAddr));
    
    // 2. Execute ReLU operation
    PPIMIR::Instruction rluInstr;
    rluInstr.type = PPIMIR::OpType::EXE;
    rluInstr.pointer = PPIMIR::OpCode::RLU;
    rluInstr.readBit = false;
    rluInstr.writeBit = false;
    rluInstr.rowAddress = 0;
    instructions.push_back(rluInstr);
    
    // 3. Store result
    instructions.push_back(generateSTB(outputAddr));
    
    return instructions;
}

std::vector<PPIMIR::Instruction> PPIMPatternMatcher::generateMPL(uint16_t input1Addr, uint16_t input2Addr, uint16_t outputAddr) {
    std::vector<PPIMIR::Instruction> instructions;
    
    // 1. Load first input
    instructions.push_back(generateLDB(input1Addr));
    
    // 2. Load second input
    instructions.push_back(generateLDB(input2Addr));
    
    // 3. Execute Max-pooling operation
    PPIMIR::Instruction mplInstr;
    mplInstr.type = PPIMIR::OpType::EXE;
    mplInstr.pointer = PPIMIR::OpCode::MPL;
    mplInstr.readBit = false;
    mplInstr.writeBit = false;
    mplInstr.rowAddress = 0;
    instructions.push_back(mplInstr);
    
    // 4. Store result
    instructions.push_back(generateSTB(outputAddr));
    
    return instructions;
}

std::vector<PPIMIR::Instruction> PPIMPatternMatcher::translateMatrixMultiply(int N) {
    std::vector<PPIMIR::Instruction> instructions;
    
    // 1. Program the cores for MAC operations
    for (int core = 0; core < 9; core++) {
        instructions.push_back(PPIMPatternMatcher::generatePRG(core));
    }
    
    // 2. Generate the nested loops
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Initialize C[i][j] to 0
            uint16_t cij_addr = (i * N + j);
            
            // Clear accumulator
            PPIMIR::Instruction clearInstr;
            clearInstr.type = PPIMIR::OpType::EXE;
            clearInstr.pointer = 0;
            clearInstr.readBit = false;
            clearInstr.writeBit = false;
            clearInstr.rowAddress = 0;
            instructions.push_back(clearInstr);
            
            for (int k = 0; k < N; k++) {
                uint16_t aik_addr = (i * N + k);
                uint16_t bkj_addr = (k * N + j);
                
                // Generate MAC operation for A[i][k] * B[k][j]
                auto macInstrs = PPIMPatternMatcher::generateMAC(aik_addr, bkj_addr, 0);
                instructions.insert(instructions.end(), macInstrs.begin(), macInstrs.end());
            }
            
            // Store the result in C[i][j]
            instructions.push_back(PPIMPatternMatcher::generateSTB(cij_addr));
        }
    }
    
    // 3. End the program
    PPIMIR::Instruction endInstr;
    endInstr.type = PPIMIR::OpType::END;
    endInstr.pointer = 0;
    endInstr.readBit = false;
    endInstr.writeBit = false;
    endInstr.rowAddress = 0;
    instructions.push_back(endInstr);
    
    return instructions;
}
