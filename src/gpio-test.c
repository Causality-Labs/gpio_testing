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
#include <unistd.h>
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

	ret = gpio_close_line_fd(line_fd_1);
	if(ret != 0)
	{
		printf("Program failed closing file descriptor for ant 1.\n");
		return 0;
	}

	ret = gpio_close_line_fd(line_fd_2);
	if(ret != 0)
	{
		printf("Program failed closing file descriptor for ant 2.\n");
		return 0;
	}

	printf("Program Completed success.\n");
	return 0;
}
