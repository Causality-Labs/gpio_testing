
#ifdef TEST

#include "unity.h"
#include "ldd_gpio_api.h"
#include "mock_syscalls.h" // Mocked system calls
#include <errno.h>
#include <fcntl.h>

void setUp(void)
{
}

void tearDown(void)
{
}

static int ioctl_callback(int fd, unsigned long request, void *arg, int cmock_num_calls);
/*
We want to test the following functions
gpio_line_request(const char *gpio_chip, const char *line_name, enum gpio_v2_line_flag line_flag, const char *line_consumer, int *fd);
int gpio_get_line_value(unsigned int line_fd, bool *state);
int gpio_close_line_fd(unsigned int line_fd);
*/

void test_gpio_line_request_valid_success(void)
{
    const char *chip_name = "/dev/virt_gpio";
    const char *line_name = "test_gpio";
    const char *consumer = "TEST_PROGRAM";
    int actual_fd = -1;
    int chip_fd = 5;
    int expected_fd = 8;

    static struct gpiochip_info chip_info = {.lines = 8};
    static struct gpio_v2_line_info line_info = {0};
    static struct gpio_v2_line_request line_request = {0};
    
    open_ExpectAndReturn(chip_name, O_RDWR, chip_fd);
    ioctl_StubWithCallback(ioctl_callback);
    // ioctl_ExpectAndReturn(chip_fd, GPIO_GET_CHIPINFO_IOCTL, &chip_info, 0);
    // ioctl_ExpectAndReturn(chip_fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info, 0);
    // ioctl_ExpectAndReturn(chip_fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info, 0);
    // ioctl_ExpectAndReturn(chip_fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info, 0);
    close_ExpectAndReturn(chip_fd,0);
    // Call the function under test
    int ret = gpio_line_request(chip_name, line_name, GPIO_V2_LINE_FLAG_INPUT, consumer, &actual_fd);

    // Assertions
    TEST_ASSERT_EQUAL_INT(0, ret); // Check for success
    TEST_ASSERT_EQUAL_INT(expected_fd, actual_fd); // Ensure the fd matches the expected value
}

static int ioctl_callback(int fd, unsigned long request, void *arg, int cmock_num_calls)
{
    if (request == GPIO_GET_CHIPINFO_IOCTL) 
    {
        struct gpiochip_info *chip_info = (struct gpiochip_info *)arg;
        chip_info->lines = 8; // Simulate 8 lines on the chip
    } 
    else if (request == GPIO_V2_GET_LINEINFO_IOCTL) 
    {
        struct gpio_v2_line_info *line_info = (struct gpio_v2_line_info *)arg;
        if (line_info->offset == 3) 
        {
            strncpy(line_info->name, "test_gpio", sizeof(line_info->name));
        } 
        else 
        {
            strncpy(line_info->name, "other_gpio", sizeof(line_info->name));
        }
    } 
    else if (request == GPIO_V2_GET_LINE_IOCTL) 
    {
        struct gpio_v2_line_request *line_request = (struct gpio_v2_line_request *)arg;
        line_request->fd = 8; // Simulate the file descriptor
    }
    return 0;
}

#endif // TEST
