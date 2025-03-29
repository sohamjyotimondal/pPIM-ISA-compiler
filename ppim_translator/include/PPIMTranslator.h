#ifndef PPIM_TRANSLATOR_H
#define PPIM_TRANSLATOR_H

#include "PPIMFrontend.h"
#include "PPIMBackend.h"
#include <string>
#include <vector>
#include <cstdint>

class PPIMTranslator {
private:
    PPIMFrontend frontend;
    PPIMBackend backend;
    
public:
    PPIMTranslator(const std::string& cppSource);
    std::vector<uint32_t> translate();
    void dumpMachineCode(const std::string& filename);
};

#endif // PPIM_TRANSLATOR_H
