#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include "ldd_gpio_api.h"

struct gpio_line gpio_line = 
{
	.name = "gps_ant_overcurrent_gpio",
	.fd = -1,
	.state = false
};

const char* rising = "rising";
const char* falling = "falling";

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	int ret = 0;
    ret = gpio_line_request("/dev/gpiochip5", gpio_line.name,
                             GPIO_V2_LINE_FLAG_INPUT | GPIO_V2_LINE_FLAG_EDGE_RISING | GPIO_V2_LINE_FLAG_EDGE_FALLING, 
                             "tests-program", &gpio_line.fd);
    if (ret != 0)
    {
      printf("%s: Could not open gpio line fd. Error: %s \n",
                     __func__, strerror(ret));
      return -1;
    }

	enum gpio_v2_line_event_id line_event;
	fd_set read_fds;
	struct timeval timeout;

	while(1)
	{
		FD_ZERO(&read_fds);
        FD_SET(gpio_line.fd, &read_fds);

        // Set timeout (optional)
        timeout.tv_sec = 5;  // Timeout in seconds
        timeout.tv_usec = 0; // Timeout in microseconds
		ret = select(gpio_line.fd + 1, &read_fds, NULL, NULL, &timeout);
		if (ret == -1)
		{
			printf("Error occurred in select(): %s\n", strerror(errno));
            break;
		}

		if (ret == 0)
		{
			printf("Nothing has happened.\n");
			continue;
		}

		if (FD_ISSET(gpio_line.fd, &read_fds))
		{
			ret = gpio_get_line_event(gpio_line.fd, &line_event);
			if (ret != 0)
			{
				printf("Error occured in when getting line event: %s\n", strerror(ret));
				continue;
			}

			printf("Line event was: %s \n",
				 (line_event == GPIO_V2_LINE_EVENT_RISING_EDGE ? rising : falling));

		}
	}

	gpio_close_line_fd(gpio_line.fd);
	
	return 0;
}
