/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#include <errno.h>


#define LECTURA 0
#define ESCRIPTURA 1

int check_fd(int fd, int permissions)
{
  if (fd!=1) return - EBADF; /*EBADF*/
  if (permissions!=ESCRIPTURA) return - EACCES; /*EACCES*/
  return 0;
}

int sys_ni_syscall()
{
	return - ENOSYS; /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

int sys_fork()
{
  int PID=-1;

  // creates the child process
  
  return PID;
}

void sys_exit()
{  
}

char buffer_copy[4];

int sys_write(int fd, char * buffer, int size)
{
	int errcode = check_fd(fd, ESCRIPTURA);
	if (errcode >= 0)
	{
		if (buffer == NULL) 
			errcode = - EFAULT;
		else if (size <= 0)
			errcode = - EINVAL;
		else 
		{
			errcode = size;
			int error = 0;
			int copied = 0;
			while (error >= 0 &&  copied < size){
				int sizeOfCopy = min(4, size - copied); 
				error = copy_from_user(buffer, buffer_copy, sizeOfCopy);
				if (error < 0) return error;
				sys_write_console(buffer_copy,sizeOfCopy);
				copied += 4;
			}
		}
	}
	return errcode;
}
