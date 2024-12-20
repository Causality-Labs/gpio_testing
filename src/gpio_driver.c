#include <stdio.h>
#include <stdint.h>
#include <linux/gpio.h>
//#include "gpio.h"
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_NO_OF_LINES_REQUESTED 1
#define GPIO_CHIP_NAME "/dev/virt_gpio"
#define CONSUMER "system_health_monitor"


int gpio_line_request(const char *line_name)
{
    assert(line_name);

    struct gpiochip_info chip_info;
    struct gpio_v2_line_info line_info;
    struct gpio_v2_line_request line_request;

    unsigned int max_no_of_lines = 0;
    unsigned int line_offset = 0;

    int ret = 0;
    bool found = false;

    int chip_fd = open(GPIO_CHIP_NAME, O_RDWR);
    if(chip_fd < 0)
    {
        perror("Error open chip file descriptor: ");
        close(chip_fd);
        return -1;
    }

    memset(&chip_info, 0, sizeof(chip_info));
    ret = ioctl(chip_fd, GPIO_GET_CHIPINFO_IOCTL, &chip_info);
	if (ret < 0)
	{	
        perror("Error getting chip line info");
        close(chip_fd);
		return ret;
	}

	
	max_no_of_lines = chip_info.lines;
    memset(&line_info, 0, sizeof(line_info));
    
    for(unsigned int index = 0; index < max_no_of_lines; index++)
	{
		line_info.offset = index;

		ret = ioctl(chip_fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info);
		if (ret < 0)
		{	
			perror("Error getting gpio chip info error message is: ");
			return ret;
		}

        if(strncmp(line_name, line_info.name, strlen(line_name)) == 0)
        {
            line_offset = line_info.offset;
            printf("string1 %s string 2 %s offset is: %d\n", line_name, line_info.name, line_offset);
            found = true;
            break;
        }
	}

    if (!found)
    {
        return -1;
    }

    memset(&line_request, 0, sizeof(line_request));
    line_request.offsets[0] = line_offset;
    line_request.config.flags = GPIO_V2_LINE_FLAG_INPUT;
    strncpy(line_request.consumer, CONSUMER, sizeof(line_request.consumer));
    line_request.num_lines = MAX_NO_OF_LINES_REQUESTED;

    ret = ioctl(chip_fd, GPIO_V2_GET_LINE_IOCTL, &line_request);
    if(ret < 0)
    {
        close(chip_fd);
        return ret;
    }

    close(chip_fd);
    return line_request.fd;
}

int gpio_get_line_value(unsigned int line_fd, bool* state)
{
    assert(state);

    struct gpio_v2_line_values line_values;

    int ret;

    memset(&line_values, 0, sizeof(line_values));
    line_values.mask = 1;

    ret = ioctl(line_fd, GPIO_V2_LINE_GET_VALUES_IOCTL, &line_values);
    if(ret < 0)
    {
        perror("Ioctl fialed getting line vales\n");
        return ret;
    }

    *state = line_values.bits == 1 ? true : false;

    return 0;
}

int gpio_close_line_fd(unsigned int line_fd)
{
    return close(line_fd);
}


