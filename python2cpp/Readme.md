# Matrix Multiplication Frontend (Python →  C++ → pPIM ISA)

A minimal C++ implementation of matrix multiplication, designed as a frontend for LLVM to generate optimized pPIM machine code. This module is callable from Python via pybind11. This provides the full pipeline from python to machine code.

## Key Features
- **C++ Frontend**: Matrix logic written in C++ for LLVM compilation in our ppim_translator file
- **LLVM Pipeline**: Compiles to LLVM IR → Machine Code → PPIM executable
- **Python API**: pybind11 exposes C++ `multiply()` function to Python