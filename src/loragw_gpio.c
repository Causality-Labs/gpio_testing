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

int gpio_line_config(uint64_t flag,  struct gpio_v2_line_config * line_config)
{
    
    memset(line_config, 0, sizeof(line_config));

    line_config->flags = flag;
	line_config->num_attrs = 1;
	line_config->attrs[0].mask = 0b1;
	line_config->attrs[0].attr.id = GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES;
	line_config->attrs[0].attr.values = 0b1;

    return 0;
}

int gpio_line_request(unsigned int gpio_pin, struct gpio_v2_line_config *config, const char *consumer)
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
    strncpy(line_request.consumer, consumer, sizeof(consumer));
    line_request.num_lines = MAX_NO_OF_LINES_REQUESTED;

    int ret = ioctl(chip_fd, GPIO_V2_GET_LINE_IOCTL, &line_request);
    if(ret == -1)
    {
        close(chip_fd);
        return -2;
    }

    if(close(chip_fd))
    {
        return -3;
    }


    return line_request.fd;
}


