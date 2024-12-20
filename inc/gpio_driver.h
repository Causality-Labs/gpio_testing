#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include <stdint.h>

int gpio_line_request(const char *line_name);
int gpio_get_line_value(unsigned int line_fd, bool* state);
int gpio_close_line_fd(unsigned int line_fd);
#endif /* GPIO_DRIVER_H_ */
