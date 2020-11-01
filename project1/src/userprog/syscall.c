#include "userprog/syscall.h"
#include "userprog/process.h"
#include <stdio.h>
#include <stdlib.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	/* My Additional Code (Project 1) : system call handler */

	switch (*(uint32_t*)(f->esp))
	{
	case SYS_HALT:
		halt();
		break;

	case SYS_EXIT:
		if (!is_user_vaddr(f->esp + 4)) exit(-1);
		exit(*(uint32_t *)(f->esp + 4));
		break;

	case SYS_EXEC:
		if (!is_user_vaddr(f->esp + 4)) exit(-1);
		f->eax = exec((const char *)*(uint32_t *)(f->esp + 4));
		break;

	case SYS_WAIT:
		if (!is_user_vaddr(f->esp + 4)) exit(-1);
		f->eax = wait((tid_t)*(uint32_t *)(f->esp + 4));
		break;

	case SYS_WRITE:
		if (!is_user_vaddr(f->esp + 20)) exit(-1);
		if (!is_user_vaddr(f->esp + 24)) exit(-1);
		if (!is_user_vaddr(f->esp + 28)) exit(-1);
		f->eax = write(*(int*)(f->esp + 20), *(void**)(f->esp + 24), *(unsigned*)(f->esp + 28));
		break;

	case SYS_READ:
		if (!is_user_vaddr(f->esp + 20)) exit(-1);
		if (!is_user_vaddr(f->esp + 24)) exit(-1);
		if (!is_user_vaddr(f->esp + 28)) exit(-1);
		f->eax = read(*(int*)(f->esp + 20), *(void**)(f->esp + 24), *(unsigned*)(f->esp + 28));
		break;

	case SYS_FIBONACCI:
		f->eax = fibonacci(*(int*)(f->esp + 4));
		break;

	case SYS_MAX_OF_FOUR_INT:
		f->eax = max_of_four_int(*(int*)(f->esp + 4), *(int*)(f->esp + 8), *(int*)(f->esp + 12), *(int*)(f->esp + 16));
		break;

	default:
		break;
	}

}

/* My Additional Code (Project 1) : system call implementation */

void halt() {
	shutdown_power_off();
}

void exit(int status) {
	printf("%s: exit(%d)\n", thread_name(), status);
	thread_current()->exit_status = status;
	thread_exit();
}

tid_t exec(const char *cmd_line) {
	return process_execute(cmd_line);
}

int wait(tid_t pid) {
	return process_wait(pid);
}

int write(int fd, const void *buffer, unsigned size) {

	if (fd == 1) {
		putbuf(buffer, size);
		return (int)size;
	}

	return -1;
}

int read(int fd, const void *buffer, unsigned size) {

	if (fd == 0) {
		for (int i = 0; i < (int)size; i++)
			buffer = input_getc();

		return (int)size;
	}

	return -1;
}

int fibonacci(int n) {
	int a = 0, b = 1;
	int tmp;

	for (int i = 0; i < n; i++) {
		tmp = b;
		b = a + b;
		a = tmp;
	}

	return a;
}

int max2(const int a, const int b) {
	return a > b ? a : b;
}

int max_of_four_int(const int a, const int b, const int c, const int d) {
	return max2(max2(a, b), max2(c, d));
}
