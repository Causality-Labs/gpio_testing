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


int gpio_line_request(size_t n, char line_name[n])
{
    struct gpiochip_info chip_info;
    struct gpio_v2_line_info line_info;
    struct gpio_v2_line_request line_request;

    unsigned int max_no_of_lines = 0;
    unsigned int line_offset = 0;

    int ret = 0;

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
		return -1;
	}

    printf("GPIO Chip Name: %s\n", chip_info.name);
    printf("GPIO Chip Label: %s\n", chip_info.label);
    printf("Number of GPIO lines: %u\n", chip_info.lines);
    printf("************************************\n");
	
	max_no_of_lines = chip_info.lines;
    memset(&line_info, 0, sizeof(line_info));
    
    for(unsigned int index = 0; index < max_no_of_lines; index++)
	{
		line_info.offset = index;

		ret = ioctl(chip_fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info);
		if (ret < 0)
		{	
			perror("Error getting gpio chip info error message is: ");
			return -1;
		}

        if(strncmp(line_name, line_info.name, n) == 0)
        {
            line_offset = line_info.offset;
            printf("Found matching string %s and the offset is %d \n", line_name, line_offset);
            close(chip_fd);
            return line_offset;
        }
        /*
		printf("Name: %s\n",line_info.name);
		printf("Consumer: %s\n",line_info.consumer);
		printf("Offset: %d\n",line_info.offset);
		printf("Num of attributes: %d\n",line_info.num_attrs);
		printf("Flags: %llu\n",line_info.flags);
		printf("************************************\n");
        */
	}

    printf("Could not find the line\n");
    return -1;


    /*
    memset(&line_request, 0, sizeof(line_request));
    line_request.offsets[0] = gpio_pin;
    line_request.config = *config;
    strncpy(line_request.consumer, CONSUMER, sizeof(line_request.consumer));
    line_request.num_lines = MAX_NO_OF_LINES_REQUESTED;

    int ret = ioctl(chip_fd, GPIO_V2_GET_LINE_IOCTL, &line_request);
    if(ret < 0)
    {
        close(chip_fd);
        return ret;
    }

    close(chip_fd);
    return line_request.fd;*/
}


