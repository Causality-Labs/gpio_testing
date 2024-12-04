#ifndef LORAGW_GPIO_H_
#define LORAGW_GPIO_H_

#include <stdint.h>
#include <linux/gpio.h>

int gpio_get_line_value(int line_fd, int value);
int get_line_value(int line_fd, struct gpio_v2_line_values *values);
int gpio_line_request(unsigned int gpio_pin, struct gpio_v2_line_config *config,  const char *consumer);

#endif /* LORAGW_GPIO_H_ */
