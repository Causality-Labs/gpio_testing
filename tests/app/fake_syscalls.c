#include "fake_syscalls.h"
#include <errno.h>
#include <string.h>
#include "ldd_gpio_api.h"

const char *test_file = "/dev/gpiochip";

int ioctl_general_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    struct gpiochip_info *chip_info;
    struct gpio_v2_line_values *line_values;
    struct gpio_v2_line_info *line_info;
    struct gpio_v2_line_request *line_request;
    int retval = 0;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
    switch (request)
    {
        case GPIO_GET_CHIPINFO_IOCTL:
            chip_info = (struct gpiochip_info *)arg;
            chip_info->lines = 8;
            retval = 0;
            break;
        case GPIO_V2_LINE_GET_VALUES_IOCTL:
            line_values = (struct gpio_v2_line_values *)arg;
            line_values->bits = 0b1;
            retval = 0;
            break;
        case GPIO_V2_GET_LINEINFO_IOCTL:
            line_info = (struct gpio_v2_line_info *)arg;
            if (line_info->offset == 3) 
            {
                strncpy(line_info->name, "test_gpio", sizeof(line_info->name));
            } 
            else 
            {
                strncpy(line_info->name, "other_gpio", sizeof(line_info->name));
            }
            retval = 0;
            break;
        case GPIO_V2_GET_LINE_IOCTL:
            line_request = (struct gpio_v2_line_request *)arg;
            line_request->fd = 16;
            retval = 0;
            break;
        default:
            errno = ENOTTY;
            retval = -1;
            break;
    }

    return retval;
}

int ioctl_getlineinfo_fail_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    struct gpiochip_info *chip_info;
    struct gpio_v2_line_values *line_values;
    struct gpio_v2_line_info *line_info;
    int retval = 0;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }

    switch (request)
    {
        case GPIO_GET_CHIPINFO_IOCTL:
            chip_info = (struct gpiochip_info *)arg;
            chip_info->lines = 8;
            retval = 0;
            break;
        case GPIO_V2_GET_LINEINFO_IOCTL:
            errno = EINVAL;
            retval = -1;
            break;
        default:
            errno = ENOTTY;
            retval = -1;
            break;
    }

    return retval;
}

int ioctl_no_line_name_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    struct gpiochip_info *chip_info;
    struct gpio_v2_line_values *line_values;
    struct gpio_v2_line_info *line_info;
    int retval = 0;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
    switch (request)
    {
        case GPIO_GET_CHIPINFO_IOCTL:
            chip_info = (struct gpiochip_info *)arg;
            chip_info->lines = 8;
            retval = 0;
            break;
        case GPIO_V2_GET_LINEINFO_IOCTL:
            line_info = (struct gpio_v2_line_info *)arg;
            strncpy(line_info->name, "other_gpio", sizeof(line_info->name));
            retval = 0;
            break;
        default:
            errno = ENOTTY;
            retval = -1;
            break;
    }

    return retval;
}

int ioctl_getline_fail_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    struct gpiochip_info *chip_info;
    struct gpio_v2_line_values *line_values;
    struct gpio_v2_line_info *line_info;
    
    int retval = 0;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
    switch (request)
    {
        case GPIO_GET_CHIPINFO_IOCTL:
            chip_info = (struct gpiochip_info *)arg;
            chip_info->lines = 8;
            retval = 0;
            break;
        case GPIO_V2_GET_LINEINFO_IOCTL:
            line_info = (struct gpio_v2_line_info *)arg;
            if (line_info->offset == 3) 
            {
                strncpy(line_info->name, "test_gpio", sizeof(line_info->name));
            } 
            else 
            {
                strncpy(line_info->name, "other_gpio", sizeof(line_info->name));
            }
            retval = 0;
            break;
        case GPIO_V2_GET_LINE_IOCTL:
            errno = EINVAL;
            retval = -1;
            break;
        default:
            errno = ENOTTY;
            retval = -1;
            break;
    }

    return retval;
}


int ioctl_resource_busy_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }

    errno = EBUSY;
    return -1;
}

int ioctl_generic_fail_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }

    errno = EINVAL;
    return -1;

}

int open_general_callback(const char *pathname, int flags, int num_calls)
{
    if(strcmp(test_file, pathname) != 0)
    {
        errno = ENOENT;
        return -1;
    }

    return 12;
}

int close_callback(int fd, int num_calls)
{
    if (fd < 0)
    {
        return EBADF;
    }

    return 0;
}

int read_rising_callback(int fd, void *arg, int count, int num_calls)
{
    struct gpio_v2_line_event *event;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
 
    event = (struct gpio_v2_line_event *)arg;
    event->id = GPIO_V2_LINE_EVENT_RISING_EDGE;

    return count;

}

int read_falling_callback(int fd, void *arg, int count, int num_calls)
{
    struct gpio_v2_line_event *event;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
 
    event = (struct gpio_v2_line_event *)arg;
    event->id = GPIO_V2_LINE_EVENT_FALLING_EDGE;

    return count;
}

int read_incomplete_callback(int fd, void *arg, int count, int num_calls)
{
    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
    
    return 0;
}

int read_unknown_event_callback(int fd, void *arg, int count, int num_calls)
{
    struct gpio_v2_line_event *event;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
 
    event = (struct gpio_v2_line_event *)arg;
    event->id = 3;

    return count;
}

int ioctl_getline_false_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    struct gpio_v2_line_values *line_values;
    int retval = 0;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
    switch (request)
    {
        case GPIO_V2_LINE_GET_VALUES_IOCTL:
            line_values = (struct gpio_v2_line_values *)arg;
            line_values->bits = 0b0;
            retval = 0;
            break;
        default:
            errno = ENOTTY;
            retval = -1;
    }

    return retval;
}
int ioctl_getline_true_callback(int fd, unsigned long request, void *arg, int num_calls)
{
    struct gpio_v2_line_values *line_values;
    int retval = 0;

    if (fd < 0)
    {
        errno = EBADF;
        return -1;
    }
    switch (request)
    {
        case GPIO_V2_LINE_GET_VALUES_IOCTL:
            line_values = (struct gpio_v2_line_values *)arg;
            line_values->bits = 0b1;
            retval = 0;
            break;
        default:
            errno = ENOTTY;
            retval = -1;
    }

    return retval;
}
