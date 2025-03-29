#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <stdexcept>
S
namespace py = pybind11;

// Matrix multiplication function
std::vector<std::vector<double>> matrix_multiply(
    const std::vector<std::vector<double>>& A, 
    const std::vector<std::vector<double>>& B) {
    if (A.empty() || B.empty()) {
        throw std::invalid_argument("Matrices cannot be empty");
    }
    size_t m = A.size();    // Rows of A
    size_t n = A[0].size(); // Columns of A
    size_t p = B[0].size(); // Columns of B

    if (n != B.size()) {
        throw std::invalid_argument("Matrix dimensions don't match for multiplication");
    }
    std::vector<std::vector<double>> C(m, std::vector<double>(p, 0.0));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            for (size_t k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}
PYBIND11_MODULE(matrix_mult, m) {
    m.doc() = "Matrix multiplication module using C++";  // Module docstring
    
    m.def("multiply", &matrix_multiply, 
          "Multiply two matrices",
          py::arg("A"), py::arg("B"));
}
