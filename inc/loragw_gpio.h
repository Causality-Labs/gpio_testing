#ifndef LORAGW_GPIO_H_
#define LORAGW_GPIO_H_

#include <stdint.h>

int open_gpio_chip(const char * gpio_chip_path);
int request_gpio_line(int gpio_chip_fd, int gpio_line);

#endif /* LORAGW_GPIO_H_ */
