import matrix_mult

# Example matrices
A = [
    [1.0, 2.0, 3.0],
    [4.0, 5.0, 6.0]
]

B = [
    [7.0, 8.0],
    [9.0, 10.0],
    [11.0, 12.0]
]

# Multiply matrices using the C++ function exposed via pybind11
C = matrix_mult.multiply(A, B)

# Print results
print("Matrix A:")
for row in A:
    print(row)

print("\nMatrix B:")
for row in B:
    print(row)

print("\nResult Matrix C = A * B:")
for row in C:
    print(row)
