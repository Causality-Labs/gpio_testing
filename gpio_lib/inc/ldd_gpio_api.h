/*
 ***************************************************************
 * Copyright (c) 2024 Tektelic Communications Inc.
 *
 * This code contains confidential information of Tektelic
 * Communications Inc.
 *
 * Tektelic makes no warranties, express, implied or otherwise,
 * regarding its accuracy, completeness or performance.
 */
/**
 * @brief   Generic logical device driver API for GPIOs.
 * @author  Ime Asamudo
 * @date    December 5, 2024
 *
 ***************************************************************
 */
#ifndef _LDD_GPIO_API_H_
#define _LDD_GPIO_API_H_

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

struct gpio_line {
    const char* name;
    int fd;
    bool state;
};

/**
 * @brief Requests a GPIO line for use.
 * @param[in] gpio_chip Name of the GPIO chip
 * @param[in] line_flag Configuration flags
 * @param[in] line_consumer Identifier for the consumer
 * @param[out] gpio_line Pointer to store gpio_line struct
 * @return 0 - success, error code or negative 1 - failure
 */
int gpio_line_request(const char* gpio_chip,
                      enum gpio_v2_line_flag line_flag,
                      const char* line_consumer,
                      struct gpio_line* gpio_line);

/**
 * @brief Reads the state of a GPIO line.
 * @param[out] gpio_line - Pointer to store gpio_line struct
 * @return 0 - success, error code - failure.
 */
int gpio_get_line_value(struct gpio_line* gpio_line);

/**
 * @brief Gets the event of a GPIO line.
 * @param[in] gpio_line - Pointer to store gpio_line struct
 * @param[out] line_event - Pointer to store the event
 * @return 0 - success, error code - failure.
 */
int gpio_get_line_event(struct gpio_line* gpio_line,
                        enum gpio_v2_line_event_id *line_event);

/**
 * @brief Closes a GPIO line.
 * @param[in] gpio_line - Pointer to store gpio_line struct
 * @return 0 - success, negative 1 - failure.
 */
int gpio_close_line_fd(struct gpio_line* gpio_line);
#endif  /* _LDD_GPIO_API_H_ */
