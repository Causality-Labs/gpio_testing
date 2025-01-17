#ifndef SYSCALLS_H
#define SYSCALLS_H

int open(const char *pathname, int flags, ...);
int close(int fd);
int ioctl(int fd, unsigned long request, void *arg);

#endif // SYSCALLS_H
