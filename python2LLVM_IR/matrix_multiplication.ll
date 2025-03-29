; ModuleID = "matrix_multiplication"
target triple = "unknown-unknown-unknown"
target datalayout = ""

define void @"matrix_multiply"(double* %"a", double* %"b", double* %"c", i32 %"n")
{
entry:
  %"i" = alloca i32
  %"j" = alloca i32
  %"k" = alloca i32
  store i32 0, i32* %"i"
  br label %"loop_i_check"
loop_i_check:
  %".8" = load i32, i32* %"i"
  %"i_cond" = icmp slt i32 %".8", %"n"
  br i1 %"i_cond", label %"loop_i_body", label %"exit"
loop_i_body:
  store i32 0, i32* %"j"
  br label %"loop_j_check"
loop_j_check:
  %".12" = load i32, i32* %"j"
  %"j_cond" = icmp slt i32 %".12", %"n"
  br i1 %"j_cond", label %"loop_j_body", label %"loop_i_end"
loop_j_body:
  %".14" = load i32, i32* %"i"
  %".15" = load i32, i32* %"j"
  %"i_times_n" = mul i32 %".14", %"n"
  %"c_idx" = add i32 %"i_times_n", %".15"
  %"ptr_c_ij" = getelementptr double, double* %"c", i32 %"c_idx"
  store double              0x0, double* %"ptr_c_ij"
  store i32 0, i32* %"k"
  br label %"loop_k_check"
loop_k_check:
  %".19" = load i32, i32* %"k"
  %"k_cond" = icmp slt i32 %".19", %"n"
  br i1 %"k_cond", label %"loop_k_body", label %"loop_j_end"
loop_k_body:
  %".21" = load i32, i32* %"i"
  %".22" = load i32, i32* %"j"
  %"i_times_n.1" = mul i32 %".21", %"n"
  %"c_idx.1" = add i32 %"i_times_n.1", %".22"
  %"ptr_c_ij.1" = getelementptr double, double* %"c", i32 %"c_idx.1"
  %"c_ij" = load double, double* %"ptr_c_ij.1"
  %".23" = load i32, i32* %"k"
  %"i_times_n.2" = mul i32 %".21", %"n"
  %"a_idx" = add i32 %"i_times_n.2", %".23"
  %"ptr_a_ik" = getelementptr double, double* %"a", i32 %"a_idx"
  %"a_ik" = load double, double* %"ptr_a_ik"
  %"k_times_n" = mul i32 %".23", %"n"
  %"b_idx" = add i32 %"k_times_n", %".22"
  %"ptr_b_kj" = getelementptr double, double* %"b", i32 %"b_idx"
  %"b_kj" = load double, double* %"ptr_b_kj"
  %"prod" = fmul double %"a_ik", %"b_kj"
  %"c_ij_new" = fadd double %"c_ij", %"prod"
  store double %"c_ij_new", double* %"ptr_c_ij.1"
  %".25" = load i32, i32* %"k"
  %"k_next" = add i32 %".25", 1
  store i32 %"k_next", i32* %"k"
  br label %"loop_k_check"
loop_j_end:
  %".28" = load i32, i32* %"j"
  %"j_next" = add i32 %".28", 1
  store i32 %"j_next", i32* %"j"
  br label %"loop_j_check"
loop_i_end:
  %".31" = load i32, i32* %"i"
  %"i_next" = add i32 %".31", 1
  store i32 %"i_next", i32* %"i"
  br label %"loop_i_check"
exit:
  ret void
}
