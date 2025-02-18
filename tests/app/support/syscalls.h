#ifndef SYSCALLS_H
#define SYSCALLS_H

int open(const char *pathname, int flag, ...);
int ioctl(int fd, unsigned long request, void *arg);
int read(int fd, void *arg, int count);
int close(int fd);

#endif // SYSCALLS_H