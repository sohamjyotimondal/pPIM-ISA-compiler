#ifndef PPIM_PATTERN_MATCHER_H
#define PPIM_PATTERN_MATCHER_H

#include "PPIMIR.h"
#include <vector>

class PPIMPatternMatcher {
public:
    static PPIMIR::Instruction generateLDB(uint16_t memoryRow);
    static PPIMIR::Instruction generateOUT(uint16_t bufferLocation);
    static PPIMIR::Instruction generateSTB(uint16_t memoryRow);
    static PPIMIR::Instruction generatePRG(uint8_t coreID);
    static std::vector<PPIMIR::Instruction> generateMAC(uint16_t inputAAddr, uint16_t inputBAddr, uint16_t outputAddr);
    static std::vector<PPIMIR::Instruction> generateRLU(uint16_t inputAddr, uint16_t outputAddr);
    static std::vector<PPIMIR::Instruction> generateMPL(uint16_t input1Addr, uint16_t input2Addr, uint16_t outputAddr);
    static std::vector<PPIMIR::Instruction> translateMatrixMultiply(int N);
};

#endif // PPIM_PATTERN_MATCHER_H
