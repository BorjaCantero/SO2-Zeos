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

int zeos_ticks;
extern struct list_head readyqueue;
extern struct list_head freequeue;

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
  if (list_empty(&freequeue)) 
		return -1;
	struct list_head * l = list_first(&freequeue);
	list_del(l);
	
	struct task_struct * h = list_head_to_task_struct(l);
	copy_data(current, h, KERNEL_STACK_SIZE);
	
	h->dir_pages_baseAddr = allocate_DIR(h);
	
	if (alloc_frame() == -1) return -1;

	page_table_entry * h_paget = get_PT(h);
	page_table_entry * p_paget = get_PT(current());	
	
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
		else if (size < 0)
			errcode = - EINVAL;
		else 
		{
			errcode = size;
			int error = 0;
			int copied = 0;
			char *buffer1 = buffer;
			while (error >= 0 &&  copied < size){
				int sizeOfCopy = min(4, size - copied); 
				error = copy_from_user(buffer1, buffer_copy, sizeOfCopy);
				if (error < 0) return error;
				sys_write_console(buffer_copy,sizeOfCopy);
				copied += 4;
				buffer1 += 4;
			}
			errcode = size;
		}
	}
	return errcode;
}

int sys_gettime(){
	return zeos_ticks;
}
