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
//#include <linux/gpio.h>
#include "gpio.h"


struct gpio_line {
    const char* name;
    int fd;
    bool state;
};


/**
 * @brief Requests a GPIO line for use.
 * @param[in] gpio_chip Name of the GPIO chip
 * @param[in] line_name Name of the GPIO line
 * @param[in] line_flag Configuration flags
 * @param[in] line_consumer Identifier for the consumer
 * @param[out] fd Pointer to store the file descriptor
 * @return 0 - success, error code or negative 1 - failure
 */
int gpio_line_request(const char* gpio_chip,
                      const char* line_name,
                      enum gpio_v2_line_flag line_flag,
                      const char* line_consumer,
                      int* fd);

/**
 * @brief Reads the state of a GPIO line.
 * @param[in] line_fd - File descriptor of the GPIO line.
 * @param[out] state - Pointer to store the state
 * @return 0 - success, error code - failure.
 */
int gpio_get_line_value(int line_fd,
                        bool* state);

/**
 * @brief Gets the event of a GPIO line.
 * @param[in] line_fd - File descriptor of the GPIO line.
 * @param[out] line_event - Pointer to store the state
 * @return 0 - success, error code - failure.
 */
int gpio_get_line_event(int line_fd,
                        enum gpio_v2_line_event_id *line_event);

/**
 * @brief Closes a GPIO line.
 * @param[in] line_fd File descriptor of the GPIO line.
 * @return 0 - success, negative 1 - failure.
 */
int gpio_close_line_fd(int line_fd);
#endif  /* _LDD_GPIO_API_H_ */
