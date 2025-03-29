# 🚀 Matrix Multiplication with LLVM IR (Python → LLVM Intermediate Representation (IR))

**Matrix Multiplication with LLVM IR** uses `llvmlite` library which is _A lightweight LLVM-Python binding for writing JIT compilers_ .We use llvmlite here to generate LLVM Intermediate Representation (IR) for a matrix multiplication function. The IR can be converted to the intended ISA using custom backend.

---

## 📝 What’s This About?

This project takes a Python implementation of matrix multiplication and translates it into LLVM IR using `llvmlite`.This bridges the gap between high-level Python code and low-level machine instructions. We can change our llvm backend from our llvm intermediate code to generate our custom ISA which is done using the ppim_translator. The compilation of an LLVM module takes the IR in textual form and feeds it into LLVM’s parsing API. It then returns a thin wrapper around LLVM’s C++ module object. This is the role of the binding layer in llvmlite which we use to create the llvmIR

---

## ✨ Features

- **LLVM IR Generation**: Generates LLVM IR for a matrix multiplication function.
- **Triple-Nested Loop Implementation**: Implements the classic algorithm for multiplying two matrices.
- **Floating-Point Operations**: Handles floating-point arithmetic (like addition and multiplication) directly in LLVM IR.
---



### How It Works

Before you dive in, make sure you have the `llvmlite` library. You can install it easily with pip: pip install llvmlite
- **Basic Blocks**: Each loop is represented as a basic block in LLVM IR.
- **Memory Access**: Matrix elements are accessed using `getelementptr`.
- **Arithmetic Operations**: Uses `fmul` (floating-point multiply) and `fadd` (floating-point add).