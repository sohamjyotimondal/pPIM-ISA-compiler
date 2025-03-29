#ifndef PPIM_BACKEND_H
#define PPIM_BACKEND_H

#include "PPIMIR.h"
#include <vector>
#include <cstdint>

class PPIMBackend {
private:
    std::vector<PPIMIR::Instruction> irInstructions;
    std::vector<uint32_t> machineCode;
    
    uint32_t encodeInstruction(PPIMIR::Instruction instr);
    
public:
    PPIMBackend(const std::vector<PPIMIR::Instruction>& ir);
    void generateMachineCode();
    std::vector<uint32_t> getMachineCode();
};

#endif // PPIM_BACKEND_H
