#ifndef SYSCALLS_H
#define SYSCALLS_H

// #include <fcntl.h>
// #include <sys/ioctl.h>
// #include <unistd.h>


int open(char *path, int flag, ...);
int ioctl(int fd, unsigned long request, void *arg);
//int close(int fd);

#endif // SYSCALLS_H

