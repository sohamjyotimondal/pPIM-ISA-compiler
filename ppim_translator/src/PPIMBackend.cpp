#include "../include/PPIMBackend.h"

PPIMBackend::PPIMBackend(const std::vector<PPIMIR::Instruction>& ir) : irInstructions(ir) {}

uint32_t PPIMBackend::encodeInstruction(PPIMIR::Instruction instr) {
    uint32_t encoded = 0;
    
    // Encode operation type (bits 18-19)
    encoded |= (instr.type & 0x3) << 18;
    
    // Encode pointer (bits 11-17)
    encoded |= (instr.pointer & 0x7F) << 11;
    
    // Encode read/write bits (bits 9-10)
    encoded |= (instr.readBit ? 1 : 0) << 10;
    encoded |= (instr.writeBit ? 1 : 0) << 9;
    
    // Encode row address (bits 0-8)
    encoded |= (instr.rowAddress & 0x1FF);
    
    return encoded;
}

void PPIMBackend::generateMachineCode() {
    for (const auto& instr : irInstructions) {
        machineCode.push_back(encodeInstruction(instr));
    }
}

std::vector<uint32_t> PPIMBackend::getMachineCode() {
    return machineCode;
}
