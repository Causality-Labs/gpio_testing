#include <fcntl.h>
#include <unistd.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
//#include "loragw_gpio.h"
#include "gpio_driver.h"

#define GPIO_BASE_PATH "/dev/virt_gpio"
const char *gpio_ant1 = "gps_ant_undercurrent_gpio";
const char *gpio_ant2 = "gps_ant_overcurrent_gpio";

int main(int argc, char *argv[])
{

	int ret = 0;
	int line_fd_1;
	int line_fd_2;
	bool state = false;

	ret = gpio_line_request(gpio_ant1);
	if (ret < 0)
	{
		printf("Program ran unsuccesfully getting ant1.\n");
		return 0;
	}
	line_fd_1 = ret;
	printf("Line fd 1 is: %d \n",line_fd_1);

	ret = gpio_line_request(gpio_ant2);
	if (ret < 0)
	{
		printf("Program ran unsuccesfully getting ant 2.\n");
		return 0;
	}
	line_fd_2 = ret;
	printf("Line fd 1 is: %d \n",line_fd_1);

	ret = gpio_get_line_value(line_fd_1, &state);
	if (ret < 0)
	{
		printf("Program ran unsuccesfully getting line value of ant 1.\n");
		return 0;
	}
	printf("State of GPIO undercurrent gpio: %d \n", state);
	
	ret = gpio_get_line_value(line_fd_2, &state);
	if (ret < 0)
	{
		printf("Program ran unsuccesfully getting value of ant 2.\n");
		return 0;
	}
	printf("State of GPIO overcurrent gpio: %d \n", state);


	/*
	struct gpiochip_info chip_info;
	struct gpio_v2_line_info line_info;
	struct gpio_v2_line_request line_request;
	struct gpio_v2_line_config line_config;
	struct gpio_v2_line_values line_values_set;
	struct gpio_v2_line_values line_values_get;
	uint64_t mask = 0b1;
	*/


	//int chip_fd = open_gpio_chip(chip_path);

	/*
	ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &chip_info);
	if (ret < 0)
	{	
		perror("Error getting gpio chip info error message is: ");
		return -1;
	}

    printf("GPIO Chip Name: %s\n", chip_info.name);
    printf("GPIO Chip Label: %s\n", chip_info.label);
    printf("Number of GPIO lines: %u\n", chip_info.lines);
    printf("************************************\n");
	
	unsigned int max_no_of_lines = chip_info.lines;
	memset(&line_info, 0, sizeof(line_info));

	
	for(unsigned int index = 0; index < max_no_of_lines; index++)
	{
		line_info.offset = index;

		ret = ioctl(fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info);
		if (ret < 0)
		{	
			perror("Error getting gpio chip info error message is: ");
			return -1;
		}
		printf("Name: %s\n",line_info.name);
		printf("Consumer: %s\n",line_info.consumer);
		printf("Offset: %d\n",line_info.offset);
		printf("Num of attributes: %d\n",line_info.num_attrs);
		printf("Flags: %llu\n",line_info.flags);
		printf("************************************\n");

	}
	*/
	//line_info.offset = offset;


	

	/*
	memset(&line_request, 0, sizeof(line_request));
    line_request.offsets[0] = offset;
	strncpy(line_request.consumer, "my_lines", GPIO_MAX_NAME_SIZE - 1);
	line_request.num_lines = 1;
	line_request.config.flags = GPIO_V2_LINE_FLAG_OUTPUT;
	line_request.config.num_attrs = 1;
	line_request.config.attrs[0].mask = 0b1;
	line_request.config.attrs[0].attr.id = GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES;
	line_request.config.attrs[0].attr.values = 0b1;



   

	ret = ioctl(fd, GPIO_V2_GET_LINE_IOCTL, &line_request);
	if (ret < 0)
	{	
		perror("Error requesting gpio line error message is: ");
		return -1;
	}

	printf("Offset[0]: %d\n", line_request.offsets[0]);
	//printf("Offset[1]: %d\n", line_request.offsets[1]);
	printf("Consumer: %s\n",line_request.consumer);
	printf("Num of Lines requested: %d\n", line_request.num_lines);
	printf("Event buffer size: %d\n", line_request.event_buffer_size);
    printf("File Descriptor: %d\n", line_request.fd);
    printf("************************************\n");


	memset(&line_values_set, 0, sizeof(line_values_set));


	line_values_set.mask = (uint64_t)0b1;
	/*
	while(1)
	{
		line_values_set.bits = (uint64_t)0b0;
		ret = ioctl(line_request.fd, GPIO_V2_LINE_SET_VALUES_IOCTL, &line_values_set);
		if (ret < 0)
		{	
			perror("Error setting gpio line error meassge is: ");
			return -1;
		}
		usleep(2);

		line_values_set.bits = (uint64_t)0b1;
		ret = ioctl(line_request.fd, GPIO_V2_LINE_SET_VALUES_IOCTL, &line_values_set);
		if (ret < 0)
		{	
			perror("Error setting gpio line error meassge is: ");
			return -1;
		}
		sleep(1);

	}
	*/
    //close(line_request.fd);	
	//close(fd);

	return 0;
}
