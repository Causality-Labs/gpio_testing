#ifndef FAKE_SYSCALLS_H
#define FAKE_SYSCALLS_H

int ioctl_general_callback(int fd, unsigned long request, void *arg, int num_calls);
int ioctl_resource_busy_callback(int fd, unsigned long request, void *arg, int num_calls);
int ioctl_getlineinfo_fail_callback(int fd, unsigned long request, void *arg, int num_calls);
int ioctl_no_line_name_callback(int fd, unsigned long request, void *arg, int num_calls);
int ioctl_getline_fail_callback(int fd, unsigned long request, void *arg, int num_calls);
int ioctl_getline_false_callback(int fd, unsigned long request, void *arg, int num_calls);
int ioctl_getline_true_callback(int fd, unsigned long request, void *arg, int num_calls);

int open_general_callback(const char *pathname, int flags, int num_calls);

int close_callback(int fd, int num_calls);

int read_rising_callback(int fd, void *arg, int count, int num_calls);
int read_falling_callback(int fd, void *arg, int count, int num_calls);
int read_incomplete_callback(int fd, void *arg, int count, int num_calls);
int read_unknown_event_callback(int fd, void *arg, int count, int num_calls);

#endif // FAKE_SYSCALLS_H