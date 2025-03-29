#include "../include/PPIMTranslator.h"
#include <fstream>
#include <iomanip>
#include <iostream>

PPIMTranslator::PPIMTranslator(const std::string& cppSource) 
    : frontend(cppSource), backend(std::vector<PPIMIR::Instruction>()) {}

std::vector<uint32_t> PPIMTranslator::translate() {
    // 1. Parse C++ code
    frontend.parse();
    
    // 2. Get IR
    auto ir = frontend.getIR();
    
    // 3. Initialize backend with IR
    backend = PPIMBackend(ir);
    
    // 4. Generate machine code
    backend.generateMachineCode();
    
    // 5. Return machine code
    return backend.getMachineCode();
}

void PPIMTranslator::dumpMachineCode(const std::string& filename) {
    auto machineCode = backend.getMachineCode();
    
    std::ofstream outFile(filename, std::ios::out);
    if (outFile.is_open()) {
        for (const auto& instr : machineCode) {
            outFile << std::hex << std::setw(6) << std::setfill('0') << instr << std::endl;
        }
        outFile.close();
        std::cout << "Machine code successfully written to " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
    }
}
