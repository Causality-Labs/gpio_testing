#ifndef LORAGW_GPIO_H_
#define LORAGW_GPIO_H_

#include <stdint.h>
#include <linux/gpio.h>

int gpio_line_config(uint64_t flag,  struct gpio_v2_line_config * line_config);
int gpio_line_request(unsigned int gpio_pin, struct gpio_v2_line_config *config,  const char *consumer);

#endif /* LORAGW_GPIO_H_ */
