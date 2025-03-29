#ifndef PPIM_FRONTEND_H
#define PPIM_FRONTEND_H

#include "PPIMIR.h"
#include <string>
#include <vector>

class PPIMFrontend {
private:
    std::string cppSource;
    std::vector<PPIMIR::Instruction> irInstructions;
    
public:
    PPIMFrontend(const std::string& source);
    void parse();
    std::vector<PPIMIR::Instruction> getIR();
};

#endif // PPIM_FRONTEND_H
