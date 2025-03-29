#include "../include/PPIMTranslator.h"
#include "../include/PPIMPatternMatcher.h"
#include <iostream>
#include <string>

int main() {
    // Sample C++ code for matrix multiplication
    std::string cppCode = R"(
        void matrixMultiply(int A[][64], int B[][64], int C[][64], int N) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    C[i][j] = 0;
                    for (int k = 0; k < N; k++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    )";
    
    std::cout << "Creating PPIM Translator..." << std::endl;
    
    // Create translator
    PPIMTranslator translator(cppCode);
    
    std::cout << "Translating C++ code to pPIM ISA..." << std::endl;
    
    // Translate C++ to machine code
    auto machineCode = translator.translate();
    
    std::cout << "Translation complete. Generated " << machineCode.size() << " instructions." << std::endl;
    
    // Dump machine code to file
    translator.dumpMachineCode("matrix_multiply.bin");
    
    return 0;
}
