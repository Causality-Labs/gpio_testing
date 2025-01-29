/*
 ***************************************************************
 * Copyright (c) 2016-2017 Tektelic Communications Inc.
 *
 * This code contains confidential information of Tektelic
 * Communications Inc.
 *
 * Tektelic makes no warranties, express, implied or otherwise,
 * regarding its accuracy, completeness or performance.
 */
/**
 * @brief   Pearl Implementation of the logical device driver for
 *          reading PSU alarm contacts
 * @author  Hubert Bugajski
 * @date    August 31, 2017
 *
 ***************************************************************/
#include <stdio.h>
#include <stdint.h>

/* #include <linux/gpio.h> */
#include "ldd_gpio_api.h"
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_NO_OF_LINES_REQUESTED 1

int gpio_line_request(const char* gpio_chip,
                      const char* line_name,
                      enum gpio_v2_line_flag line_flag,
                      const char* line_consumer,
                      int* fd)
{
    struct gpiochip_info chip_info;
    struct gpio_v2_line_info line_info;
    struct gpio_v2_line_request line_request;

    unsigned int max_no_of_lines = 0;
    unsigned int line_offset = 0;

    int ret = 0;
    bool found = false;

    int chip_fd = open(gpio_chip, O_RDWR);

    if (chip_fd < 0)
    {
        ret = errno;
        return ret;
    }

    memset(&chip_info, 0, sizeof(chip_info));
    ret = ioctl(chip_fd, GPIO_GET_CHIPINFO_IOCTL, &chip_info);

    if (ret < 0)
    {
        ret = errno;
        close(chip_fd);
        return ret;
    }


    max_no_of_lines = chip_info.lines;
    memset(&line_info, 0, sizeof(line_info));

    for (unsigned int index = 0; index < max_no_of_lines; index++)
    {
        line_info.offset = index;

        ret = ioctl(chip_fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info);

        if (ret < 0)
        {
            ret = errno;
            close(chip_fd);
            return ret;
        }

        if (strncmp(line_name, line_info.name, strlen(line_name)) == 0)
        {
            line_offset = line_info.offset;
            found = true;
            break;
        }
    }

    if (!found)
    {
        close(chip_fd);
        return ENODEV;
    }

    memset(&line_request, 0, sizeof(line_request));
    line_request.offsets[0] = line_offset;
    line_request.config.flags = line_flag;
    strncpy(line_request.consumer, line_consumer, sizeof(line_request.consumer));
    line_request.num_lines = MAX_NO_OF_LINES_REQUESTED;

    ret = ioctl(chip_fd, GPIO_V2_GET_LINE_IOCTL, &line_request);

    if (ret < 0)
    {
        ret = errno;
        close(chip_fd);
        return ret;
    }

    close(chip_fd);
    *fd = line_request.fd;
    return 0;
}

int gpio_get_line_value(int line_fd, bool* state)
{
    struct gpio_v2_line_values line_values;

    int ret;

    memset(&line_values, 0, sizeof(line_values));
    line_values.mask = 1;

    ret = ioctl(line_fd, GPIO_V2_LINE_GET_VALUES_IOCTL, &line_values);

    if (ret < 0)
    {
        ret = errno;
        return ret;
    }

    *state = line_values.bits;

    return 0;
}

int gpio_get_line_event(int line_fd, enum gpio_v2_line_event_id *line_event)
{
    int ret = 0;

    struct gpio_v2_line_event event;
    memset(&event, 0, sizeof(event));

    ret = read(line_fd,  &event, sizeof(event));

    if (ret == -1)
    {
        ret = errno;
        return ret;
    }

    if (ret != sizeof(event))
    {
        return EBADE;
    }

    switch (event.id)
    {
        case GPIO_V2_LINE_EVENT_RISING_EDGE:
        case GPIO_V2_LINE_EVENT_FALLING_EDGE:
            *line_event = event.id;
            return 0;
        default:
            return EINVAL;
    }

}

int gpio_close_line_fd(int line_fd)
{
    return close(line_fd);
}
