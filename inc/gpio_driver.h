#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include <stdint.h>

int gpio_line_request(size_t n, const char line_name[n]);

#endif /* GPIO_DRIVER_H_ */
