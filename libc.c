/*
 * libc.c 
 */

#include <libc.h>

#include <types.h>

int errno;

void itoa(int a, char *b)
{
  int i, i1;
  char c;
  
  if (a==0) { b[0]='0'; b[1]=0; return ;}
  
  i=0;
  while (a>0)
  {
    b[i]=(a%10)+'0';
    a=a/10;
    i++;
  }
  
  for (i1=0; i1<i/2; i1++)
  {
    c=b[i1];
    b[i1]=b[i-i1-1];
    b[i-i1-1]=c;
  }
  b[i]=0;
}

int strlen(char *a)
{
  int i;
  
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}

int write(int fd, char * buffer, int size){
  int resultat;
  __asm__ volatile(
          "movl %1, %%ebx;"
          "movl %2, %%ecx;"
          "movl %3, %%edx;"
          "movl $4, %%eax;"
          "int $0x80;"
          "movl %%eax, %0;"
          : "=g" (resultat)
          : "g" (fd), "g"(buffer), "g" (size)
          : "ax", "bx", "cx", "dx"
    );

}

