#include <stdio.h>
#include <stdint.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAX_NO_OF_LINES_REQUESTED 1
#define GPIO_CHIP_NAME "/dev/virt_gpio"
#define CONSUMER "system_health_monitor"


int gpio_get_line_value(unsigned int gpio_pin, int* value)
{
    int ret;
    int line_fd;
    struct gpio_v2_line_config config;
	struct gpio_v2_line_values lv;

    memset(&config, 0, sizeof(config));
    config.flags = GPIO_V2_LINE_FLAG_INPUT;
    ret = gpio_line_request(gpio_pin, &config);
    if (ret < 0)
    {
        return ret;
    }

    int line_fd = ret;
    lv.mask = 0b1;

    ret = get_line_value(line_fd, &lv);
    if (ret < 0)
    {
        return ret;
    }
    *value = lv.bits;

    close(line_fd);
    return 0;

}

int get_line_value(int line_fd, struct gpio_v2_line_values *values)
{
    int ret;

    ret = ioctl(line_fd, GPIO_V2_LINE_GET_VALUES_IOCTL, values);
    if(ret == -1)
    {
        return ret;
    }

    return ret;

}

int gpio_line_request(unsigned int gpio_pin, struct gpio_v2_line_config *config)
{

    struct gpio_v2_line_request line_request;

    int chip_fd = open(GPIO_CHIP_NAME, O_RDWR);
    if(chip_fd == -1)
    {
        return -1;
    }

    memset(&line_request, 0, sizeof(line_request));
    line_request.offsets[0] = gpio_pin;
    line_request.config = *config;
    strncpy(line_request.consumer, CONSUMER, sizeof(CONSUMER));
    line_request.num_lines = MAX_NO_OF_LINES_REQUESTED;

    int ret = ioctl(chip_fd, GPIO_V2_GET_LINE_IOCTL, &line_request);
    if(ret == -1)
    {
        close(chip_fd);
        return -2;
    }

    close(chip_fd);
    return line_request.fd;
}


