#include <libc.h>

char buff[24];

int pid;

int add(int par1, int par2) 
{
	return par1 + par2;
}

/**int escriu(int fd, char * buffer, int size) {
	int resultat = -1;
	int errno = -1;

	__asm__ __volatile__(
          "movl %1, %%ebx;"
          "movl %2, %%ecx;"
          "movl %3, %%edx;"
          "movl $0x04, %%eax;"
          "sysenter;"
          "movl %%eax, %0;"
          : "=g" (resultat)
          : "g" (fd), "g"(buffer), "g" (size)
          : "ax", "bx", "cx", "dx"
    );

    if (resultat < 0){
	    errno = resultat;
		return -1;
	}
	else return resultat;
}**/

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

	/*
	// JOC PROVES RANG
    runjp_rank(0,1);
    */
    
	// JOCS DE PROVES
    //runjp();
    
	/*
	// TEST WRITE
    write(1, "HolaMon\nHolaMon\n", 16);
    */
    
	/*
	// TEST GETTIME 
    char* a = "";
	itoa(gettime(), a);
	write(1, a, strlen(a));
	*/
    
	while(1) { 
	}
}
