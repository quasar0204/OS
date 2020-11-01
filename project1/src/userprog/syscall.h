#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "threads/thread.h"

void syscall_init(void);

void halt(void);
void exit(int status);
tid_t exec(const char *cmd_line);
int wait(tid_t pid);
int write(int fd, const void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
int fibonacci(int n);
int max2(const int a, const int b);
int max_of_four_int(const int a, const int b, const int c, const int d);

#endif /* userprog/syscall.h */
