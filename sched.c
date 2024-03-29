/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>
#include <list.h>
#include <utils.h>

union task_union task[NR_TASKS]
  __attribute__((__section__(".data.task")));

struct list_head freequeue;
struct list_head readyqueue;

struct task_struct* idle_task;

#if 1
struct task_struct *list_head_to_task_struct(struct list_head *l)
{
  return list_entry( l, struct task_struct, list);
}
#endif

extern struct list_head blocked;


/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) 
{
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) 
{
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}


page_table_entry * allocate_DIR(struct task_struct *t)
{
	int pos;

	pos = ((int)t-(int)task)/sizeof(union task_union);

	return (page_table_entry*) &dir_pages[pos];
}

void inner_task_switch(union task_union* new){

	//posa els valors d'on es troba la pila del nou proces
	tss.esp0 = KERNEL_ESP((union task_union*) new);
	writeMSR(0x175, KERNEL_ESP((union task_union*) new));

	struct task_struct* newTask = &new->task;

	//guardar valor ebp del proces antic
	current()->kernel_esp = get_ebp();

	//canviar el system stack al del nou proces
	change_system_stack(newTask->kernel_esp);
	
	set_cr3(get_DIR(newTask));
} 

void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");

	while(1)
	{
		//sys_write(1, "IDLE\n", 5);
	}
}

void init_idle (void)
{
	struct list_head * l = list_first(&freequeue);
	list_del(l);
	
	struct task_struct * t = list_head_to_task_struct(l);
	t->PID = 0;
	t->dir_pages_baseAddr = allocate_DIR(t);
	set_user_pages(t);
	
	unsigned int* p = ((unsigned int) KERNEL_ESP((union task_union*) t) - 4);
	*p = &cpu_idle;
	p -= 1;
	*p = 0;
	t->kernel_esp = p;
	
	idle_task = t;
}

void init_task1(void)
{
	struct list_head * l = list_first(&freequeue);
	list_del(l);
	
	struct task_struct * t = list_head_to_task_struct(l);
	t->PID = 1;
	t->dir_pages_baseAddr = allocate_DIR(t);
	set_user_pages(t);
	
	tss.esp0 = KERNEL_ESP((union task_union*) t);
	writeMSR(0x175, KERNEL_ESP((union task_union*) t));
	set_cr3(get_DIR(t));
}


void init_sched()
{
	INIT_LIST_HEAD(&freequeue);
	
	for (int i = 0; i < NR_TASKS; i++) {
		list_add_tail(&(task[i].task.list), list_first(&freequeue));
	}
	
	INIT_LIST_HEAD(&readyqueue);
}

struct task_struct* current()
{
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );
  return (struct task_struct*)(ret_value&0xfffff000);
}

