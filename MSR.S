
#include <asm.h>

ENTRY(writeMSR)
	push %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ecx
	movl 12(%ebp), %eax
	xor %edx, %edx
	wrmsr
	movl %ebp, %esp
	pop %ebp
	ret