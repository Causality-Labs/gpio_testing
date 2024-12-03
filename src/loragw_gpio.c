#include <stdio.h>
#include <stdint.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#define GPIO_BASE_PATH "/dev/virt_gpio"

int open_gpio_chip(const char * gpio_chip_path)
{
    return open(gpio_chip_path, O_RDWR);
}

int request_gpio_line(const char * gpio_chip_fd, int gpio_line);
{

    struct gpio_v2_line_request line_request;

    int chip_fd = open(gpio_chip_path, O_RDWR);
    memset(&line_request, 0, sizeof(line_request));


    return 0;
}
