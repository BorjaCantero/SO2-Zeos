# 1 "MSR.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "MSR.S"

# 1 "include/asm.h" 1
# 3 "MSR.S" 2

.globl writeMSR; .type writeMSR, @function; .align 0; writeMSR:
 push %ebp
 movl %esp, %ebp
 movl 8(%ebp), %ecx
 movl 12(%ebp), %eax
 xor %edx, %edx
 wrmsr
 movl %ebp, %esp
 pop %ebp
 ret
