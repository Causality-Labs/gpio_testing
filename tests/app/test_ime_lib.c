#include "unity.h"
#include "ime_lib.h"
#include "mock_Display.h"
#include "mock_syscalls.h"
#include <string.h>
#include <linux/gpio.h>
#include <errno.h>

#define EXISTING_FILE "here"
#define NON_EXISTING_FILE "not_here"

int Draw_Int_Callback(int x, int num_calls);
int open_Callback(const char *pathname, int flags, int num_calls);
int ioctl_Callback(int fd, unsigned long request, void *arg, int num_calls);

void setUp(void)
{
}
 
void tearDown(void)
{
}
 
/*******************************************************************************
 *    TESTS
 ******************************************************************************/
 
void test_add_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(2,add_numbers(1,1));
}


void test_MakePoint_creates_new_point(void)
{
    struct point pt = MakePoint(3,4);
    TEST_ASSERT_EQUAL_INT(3,pt.x);
    TEST_ASSERT_EQUAL_INT(4,pt.y);
}

void test_MakePoint_Draw_Coordinates_pass(void)
{
    int ret = 0;
    Draw_Int_StubWithCallback(Draw_Int_Callback);
    ret = init_Display(3, 4);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_MakePoint_Draw_Coordinates_fail(void)
{
    int ret = 0;
    Draw_Int_StubWithCallback(Draw_Int_Callback);
    ret = init_Display(-3, -4);
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

void test_ime_open_valid(void)
{
    int ret = 0 ;
    open_StubWithCallback(open_Callback);
    ret = ime_open(EXISTING_FILE);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_ime_open_invalid(void)
{
    int ret = 0;
    open_StubWithCallback(open_Callback);

    ret = ime_open(NON_EXISTING_FILE);
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

void test_ime_ioctl_valid(void)
{
    int ret = 0;
    int fd = 2;
    struct gpiochip_info chip_info = {0};
    ioctl_StubWithCallback(ioctl_Callback);

    ret = ime_ioctl(fd, GPIO_GET_CHIPINFO_IOCTL);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_ime_ioctl_invalid_fd_with_errno(void)
{
    int ret = 0;
    int fd = -1;
    struct gpiochip_info chip_info = {0};
    ioctl_StubWithCallback(ioctl_Callback);

    ret = ime_ioctl(fd, GPIO_GET_CHIPINFO_IOCTL);
    TEST_ASSERT_EQUAL_INT(EBADF , ret);
}

void test_ime_ioctl_invalid_with_errno(void)
{
    int ret = 0;
    int fd = 5;
    struct gpiochip_info chip_info = {0};
    ioctl_StubWithCallback(ioctl_Callback);

    ret = ime_ioctl(fd, 0xFFFF);
    TEST_ASSERT_EQUAL_INT(ENOTTY, ret);
}

int Draw_Int_Callback(int x, int num_calls)
{
    if(x < 0)
    {
        return -1;
    }
    return 0;
}

int open_Callback(const char *pathname, int flags, int num_calls)
{
    if (strncmp(pathname, EXISTING_FILE, strlen(pathname)) != 0)
    {
        return  -1;
    }
    return 0;
}

int ioctl_Callback(int fd, unsigned long request, void *arg, int num_calls)
{
    struct gpiochip_info *chip_info;
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
            break;
        default:
            errno = ENOTTY;
            return -1;
    }

    return 0;
}