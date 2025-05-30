# pPIM Compiler Pipeline 

**Translate C++/Python to pPIM ISA**  
A hybrid architecture for a cpp compiler that bridges high-level code (C++/Python) to ISA for pPIM architecture.

## Key Features
- **24-bit ISA Support**: Native encoding for pPIM operations (NOOP, PROG, MAC ,EXEC)
- **Dual Frontends**:  
  - **C++**: Classic compiler workflow (source → IR → pPIM binary)  
  - **Python**: Direct LLVM IR generation via `llvmlite` or cpp code via pybind11 bindings.
- **Smart Pattern Matching**: Auto-converts matrix ops → pPIM instruction sequences
- **Nested Loop Optimization**: Specialized handling for data-parallel workloads

## How It Works

[Python/C++ Code]
→ (Frontend) → [Optimized IR]
→ (Pattern Matcher) → [pPIM Instructions]
→ (Backend) → [Executable .ppimbin]
![Instruction Format](https://github.com/sohamjyotimondal/pPIM-ISA-compiler/blob/main/results/architecture.jpg)


## Dependencies
1. **Install Tools**:  
    pip install pybind11 llvmlite
    make install-deps # Requires GCC 14+

# pPIM ISA Instruction Format (24-bit Fixed Length)

| Bits 18-7 | Bits 11-16         | Bits 9-10    | Bits 0-8     |
|------------|--------------------|--------------|--------------|
| Operation  | READ Ptr. / CORE Ptr | RD / WR Ctrl | ROW Address |

---

### **Field Breakdown**

1. **Operation (Bits 18-17)**:
   - Specifies the type of instruction:
     - `00`: NOOP (No Operation)
     - `01`: PROG (Programming cores with new functionality)
     - `10`: EXE (Execute operations within the cluster)
     - `11`: END (Terminate operation and reset registers)

2. **READ Ptr. / CORE Ptr (Bits 11-16)**:
   - Points to the specific core or cluster for routing data or control signals.

3. **RD / WR Control Bits (Bits 9-10)**:
   - **Read Bit (Bit 10)**: Set high to read data from memory rows into the cluster's read buffer.
   - **Write Bit (Bit 9)**: Set high to write data from the cluster's write buffer into memory rows.
   - **Priority**: If both bits are set, read operation takes precedence.

4. **ROW Address (Bits 0-8)**:
   - Specifies the target row in memory for read/write operations.
   - Supports addressing up to **512 rows** per subarray.
     
## Result
### **Final Machine Code**

![Final MACHINE CODE](https://github.com/user-attachments/assets/da02f006-82d2-4073-9100-f83465a9f13c)

### **Python to CPP Code**
  - This helps us use Python as our HLL and convert to the given machine code using the existing pipeline via cpp
  - [Readme](python2cpp/Readme.md)
    
### **Python to Intermediate Representation**
  - A more direct pipeline to convert to llvm IR directly using llvmlite
  - [Readme](python2LLVM_IR/Readme.md)
  - [Intermediate code](python2LLVM_IR/matrix_multiplication.ll)



