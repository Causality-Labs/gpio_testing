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
#include "loragw_gpio.h"

int main(int argc, char *argv[])
{	
	/*
	struct gpiochip_info chip_info;
	struct gpio_v2_line_info line_info;
	struct gpio_v2_line_request line_request;
	struct gpio_v2_line_config line_config;
	struct gpio_v2_line_values line_values_set;
	struct gpio_v2_line_values line_values_get;
	uint64_t mask = 0b1;
	*/

	static const char *chip_path = "/dev/virt_gpio";
	int ret = 0;
	bool is_present = false;
	int fd = open(chip_path, O_RDWR);

	if(fd < 0)
	{
		printf("Error Opening chip file.\n");

		return -1;
	}
	
	for(unsigned int index = 0; index < 20; index++)
	{
		is_present = is_gpio_pin_exported(fd, index);
		if(!is_present)
		{
			printf("Pin %d does not exist.\n", index);
		}

		printf("Pin %d exist.\n", index);
	}
	
	close(fd);
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
