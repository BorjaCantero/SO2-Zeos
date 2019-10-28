# 1 "wrapper.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "wrapper.S"

# 1 "include/asm.h" 1
# 3 "wrapper.S" 2

# Wrapper for the write function
.globl write_wrapper; .type write_wrapper, @function; .align 0; write_wrapper:
 pushl %ebp
 movl %esp,%ebp

 #save all used registers
 pushl %ebx
 pushl %ecx
 pushl %edx
 pushl %edi

 #read parameters
 movl 8(%ebp), %ebx
 movl 12(%ebp), %ecx
 movl 16(%ebp), %edx

 #save the return address
 leal return_sys_write, %edi

 pushl %ecx
 pushl %edx
 pushl %edi

 #select write from syscall table
 movl $4, %eax

 push %ebp
 movl %esp, %ebp

 #entering system call
 sysenter

return_sys_write:

 popl %ebp
 add $4, %esp #erase the return_sys_write address
 popl %edx
 popl %ecx

 cmp $0, %eax
 jge fi_write_wrapper

 #in case there was an error, copy it to errno
 leal errno, %edx
 neg %eax
 movl %eax, (%edx)
 movl $-1, %eax

fi_write_wrapper:
 #retrieve all used register's data
 popl %edi
 popl %edx
 popl %ecx
 popl %ebx

 movl %ebp, %esp
 popl %ebp
 ret


.globl gettime_wrapper; .type gettime_wrapper, @function; .align 0; gettime_wrapper:
 pushl %ebp
 movl %esp,%ebp

 #save all used registers
 pushl %edi


 #save the return address
 leal return_sys_clock, %edi

 pushl %edi

 #select write from syscall table
 movl $10, %eax

 push %ebp
 movl %esp, %ebp

 #entering system call
 sysenter

return_sys_clock:

 popl %ebp
 add $4, %esp #erase the return_sys_clock address

 #retrieve all used register's data
 popl %edi

 movl %ebp, %esp
 popl %ebp
 ret

.globl getpid; .type getpid, @function; .align 0; getpid:
 pushl %ebp
 movl %esp, %ebp

 pushl %edi

 leal return_sys_getpid, %edi

 pushl %edi

 movl $20, %eax
 pushl %ebp
 movl %esp, %ebp

 sysenter

return_sys_getpid:

 popl %ebp
 add $4, %esp

 popl %edi

 movl %ebp, %esp
 popl %ebp
 ret

.globl fork; .type fork, @function; .align 0; fork:
 pushl %ebp
 movl %esp, %ebp

 pushl %edi

 leal return_sys_fork, %edi

 pushl %edi

 movl $2, %eax
 pushl %ebp
 movl %esp, %ebp

 sysenter

return_sys_fork:

 popl %ebp
 add $4, %esp

 popl %edi

 movl %ebp, %esp
 popl %ebp
 ret
