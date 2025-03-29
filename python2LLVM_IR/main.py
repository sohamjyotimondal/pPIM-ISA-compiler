import llvmlite.ir as ir
import llvmlite.binding as llvm


llvm.initialize()
llvm.initialize_native_target()
llvm.initialize_native_asmprinter()
module = ir.Module(name="matrix_multiplication")

# A, B are input matrices, C is the output matrix, and n is the matix size
double_ptr_type = ir.PointerType(ir.DoubleType())
int32_type = ir.IntType(32)
func_type = ir.FunctionType(
    ir.VoidType(), [double_ptr_type, double_ptr_type, double_ptr_type, int32_type]
)

func = ir.Function(module, func_type, name="matrix_multiply")
a_ptr, b_ptr, c_ptr, n = func.args
a_ptr.name = "a"
b_ptr.name = "b"
c_ptr.name = "c"
n.name = "n"
entry_block = func.append_basic_block(name="entry")
loop_i_check = func.append_basic_block(name="loop_i_check")
loop_i_body = func.append_basic_block(name="loop_i_body")
loop_j_check = func.append_basic_block(name="loop_j_check")
loop_j_body = func.append_basic_block(name="loop_j_body")
loop_k_check = func.append_basic_block(name="loop_k_check")
loop_k_body = func.append_basic_block(name="loop_k_body")
loop_j_end = func.append_basic_block(name="loop_j_end")
loop_i_end = func.append_basic_block(name="loop_i_end")
exit_block = func.append_basic_block(name="exit")

# Initialize loop variables on Entry
builder = ir.IRBuilder(entry_block)
i = builder.alloca(int32_type, name="i")
j = builder.alloca(int32_type, name="j")
k = builder.alloca(int32_type, name="k")
builder.store(ir.Constant(int32_type, 0), i)
builder.branch(loop_i_check)

# i loop condition: i < n
builder.position_at_end(loop_i_check)
i_val = builder.load(i)
cond_i = builder.icmp_signed("<", i_val, n, name="i_cond")
builder.cbranch(cond_i, loop_i_body, exit_block)
# i loop body
builder.position_at_end(loop_i_body)
builder.store(ir.Constant(int32_type, 0), j)
builder.branch(loop_j_check)


# j loop condition: j < n
builder.position_at_end(loop_j_check)
j_val = builder.load(j)
cond_j = builder.icmp_signed("<", j_val, n, name="j_cond")
builder.cbranch(cond_j, loop_j_body, loop_i_end)

# j loop body
builder.position_at_end(loop_j_body)
# Initialize C[i][j] to 0
i_val = builder.load(i)
j_val = builder.load(j)
i_times_n = builder.mul(i_val, n, name="i_times_n")
c_idx = builder.add(i_times_n, j_val, name="c_idx")
ptr_c_ij = builder.gep(c_ptr, [c_idx], name="ptr_c_ij")
builder.store(ir.Constant(ir.DoubleType(), 0.0), ptr_c_ij)

# Initialize k to 0
builder.store(ir.Constant(int32_type, 0), k)
builder.branch(loop_k_check)

# k loop condition: k < n
builder.position_at_end(loop_k_check)
k_val = builder.load(k)
cond_k = builder.icmp_signed("<", k_val, n, name="k_cond")
builder.cbranch(cond_k, loop_k_body, loop_j_end)

# This implements C[i][j] += A[i][k] * B[k][j]
builder.position_at_end(loop_k_body)
# Load C[i][j]
i_val = builder.load(i)
j_val = builder.load(j)
i_times_n = builder.mul(i_val, n, name="i_times_n")
c_idx = builder.add(i_times_n, j_val, name="c_idx")
ptr_c_ij = builder.gep(c_ptr, [c_idx], name="ptr_c_ij")
c_ij = builder.load(ptr_c_ij, name="c_ij")

# Load A[i][k]
k_val = builder.load(k)
i_times_n = builder.mul(i_val, n, name="i_times_n")
a_idx = builder.add(i_times_n, k_val, name="a_idx")
ptr_a_ik = builder.gep(a_ptr, [a_idx], name="ptr_a_ik")
a_ik = builder.load(ptr_a_ik, name="a_ik")

# Load B[k][j]
k_times_n = builder.mul(k_val, n, name="k_times_n")
b_idx = builder.add(k_times_n, j_val, name="b_idx")
ptr_b_kj = builder.gep(b_ptr, [b_idx], name="ptr_b_kj")
b_kj = builder.load(ptr_b_kj, name="b_kj")

# C[i][j] += A[i][k] * B[k][j]
prod = builder.fmul(a_ik, b_kj, name="prod")
c_ij_new = builder.fadd(c_ij, prod, name="c_ij_new")
builder.store(c_ij_new, ptr_c_ij)

# Increment k
k_val = builder.load(k)
k_next = builder.add(k_val, ir.Constant(int32_type, 1), name="k_next")
builder.store(k_next, k)
builder.branch(loop_k_check)

# j loop end: increment j and continue
builder.position_at_end(loop_j_end)
j_val = builder.load(j)
j_next = builder.add(j_val, ir.Constant(int32_type, 1), name="j_next")
builder.store(j_next, j)
builder.branch(loop_j_check)

# i loop end: increment i and continue
builder.position_at_end(loop_i_end)
i_val = builder.load(i)
i_next = builder.add(i_val, ir.Constant(int32_type, 1), name="i_next")
builder.store(i_next, i)
builder.branch(loop_i_check)

# Exit block: return
builder.position_at_end(exit_block)
builder.ret_void()

# Print the generated LLVM IR
with open("matrix_multiplication.ll", "w") as f:
    f.write(str(module))
