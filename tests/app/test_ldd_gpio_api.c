#include "unity.h"
#include "ldd_gpio_api.h"
#include "mock_syscalls.h"
#include "fake_syscalls.h"
#include <errno.h>

void setUp(void)
{
}
 
void tearDown(void)
{
}

/*******************************************************************************
 *    gpio_get_line_value unit tests
 ******************************************************************************/

/*
 * Verify gpio_get_line_value() handles an invalid file descriptor (-1) by returning EBADF 
 * and leaving the state unchanged.
 */
void test_gpio_get_line_invalid_fd_fail(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    ioctl_StubWithCallback(ioctl_general_callback);

    ret = gpio_get_line_value(&test_gpio_line);

    TEST_ASSERT_EQUAL_INT(EBADF, ret);
    TEST_ASSERT_FALSE(test_gpio_line.state);
}

/*
 * Verify gpio_get_line_value() handles a busy resource by returning EBUSY 
 * and leaving the state unchanged.
 */
void test_gpio_get_line_state_resource_busy_fail(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = false
    };

    ioctl_StubWithCallback(ioctl_resource_busy_callback);

    ret = gpio_get_line_value(&test_gpio_line);

    TEST_ASSERT_EQUAL_INT(EBUSY, ret);
    TEST_ASSERT_FALSE(test_gpio_line.state);
}

/*
 * Verify gpio_get_line_value() correctly handles a GPIO line that remains in the false state, 
 * returning success (0) and keeping the state unchanged.
 */
void test_gpio_get_line_state_false_to_false_success(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = false
    };

    ioctl_StubWithCallback(ioctl_getline_false_callback);

    ret = gpio_get_line_value(&test_gpio_line);

    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_FALSE(test_gpio_line.state);
}

/*
 * Verify gpio_get_line_value() correctly updates the GPIO line state from false to true,
 * returning success (0) and setting state to true.
 */
void test_gpio_get_line_state_false_to_true_success(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = false
    };

    ioctl_StubWithCallback(ioctl_getline_true_callback);

    ret = gpio_get_line_value(&test_gpio_line);

    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_TRUE(test_gpio_line.state);
}

/*
 * Verify gpio_get_line_value() correctly updates the GPIO line state from true to false,
 * returning success (0) and setting state to false.
 */
void test_gpio_get_line_state_true_to_false_success(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = true
    };

    ioctl_StubWithCallback(ioctl_getline_false_callback);

    ret = gpio_get_line_value(&test_gpio_line);

    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_FALSE(test_gpio_line.state);
}


/*
 * Verify gpio_get_line_value() correctly maintains the GPIO line state as true,
 * returning success (0) and keeping state unchanged.
 */
void test_gpio_get_line_state_true_to_true_success(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = true
    };

    ioctl_StubWithCallback(ioctl_getline_true_callback);

    ret = gpio_get_line_value(&test_gpio_line);

    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_TRUE(test_gpio_line.state);
}


/*******************************************************************************
 *    gpio_line_request unit tests
 ******************************************************************************/

/*
 * Verify gpio_line_request() returns ENOENT when provided with an invalid GPIO chip path.
 * The function should fail and leave the file descriptor unchanged (-1).
 */
void test_gpio_line_request_invalid_file_name_fail(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/no_gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "test_program";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(ENOENT, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd);
}

/*
 * Verify gpio_line_request() returns EBUSY when the ioctl call to retrieve chip info fails.
 * The function should properly close the file descriptor and return the error.
 */
void test_gpio_line_request_invalid_chipinfo_ioctl_fail(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "test_program";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_resource_busy_callback);
    close_StubWithCallback(close_callback);


    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(EBUSY, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd);
}

/*
 * Verify gpio_line_request() returns EINVAL when the ioctl call to retrieve line info fails.
 * The function should properly close the file descriptor and return the error.
 */
void test_gpio_line_request_invalid_lineinfo_ioctl_fail(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "test_program";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_getlineinfo_fail_callback);
    close_StubWithCallback(close_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(EINVAL, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd);
}

/*
 * Verify gpio_line_request() returns ENODEV when the requested GPIO line is not found.
 * The function should properly close the file descriptor and return the error.
 */
void test_gpio_line_request_line_not_found_fail(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "test_program";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_no_line_name_callback);
    close_StubWithCallback(close_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(ENODEV, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd);

}

/*
 * Verify gpio_line_request() returns ENODEV when the requested line name almost matches
 * an existing GPIO line but is not an exact match.
 */
void test_gpio_line_request_line_almost_match_fails(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "test_program";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio123",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_general_callback);
    close_StubWithCallback(close_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(ENODEV, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd);

}

/*
 * Verify gpio_line_request() returns ENAMETOOLONG when the consumer string 
 * exceeds the maximum allowed length of 32 characters.
 * This test uses a 33-character string (including the null terminator).
 */
void test_gpio_line_request_line_consumer_33_characters_fail(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "ThisStringHasExactlyThirtyThree!";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_general_callback);
    close_StubWithCallback(close_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(ENAMETOOLONG, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd);
}

/*
 * Verify gpio_line_request() returns ENAMETOOLONG when the consumer string 
 * significantly exceeds the maximum allowed length of 32 characters.
 * This test uses a 55-character string (including the null terminator).
 */
void test_gpio_line_request_line_consumer_55_characters_fail(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer =  "ThisStringIsDefinitelyLongerThanThirtyTwoCharacters!";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_general_callback);
    close_StubWithCallback(close_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(ENAMETOOLONG, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd);
}

/*
 * Verify gpio_line_request() returns EINVAL when ioctl fails during 
 * the GPIO_V2_GET_LINE_IOCTL request.
 */
void test_gpio_line_request_invalid_getline_ioctl_fail(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "test_program";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_getline_fail_callback);
    close_StubWithCallback(close_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(EINVAL, ret);
    TEST_ASSERT_EQUAL_INT(-1, test_gpio_line.fd); 
}

/*
 * Verify gpio_line_request() successfully requests a GPIO line 
 * and assigns a valid file descriptor.
 */
void test_gpio_line_request_success(void)
{
    int ret = 0;
    const char *gpio_chip = "/dev/gpiochip";
    enum gpio_v2_line_flag line_flag = GPIO_V2_LINE_FLAG_INPUT;
    const char *consumer = "test_program";

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };

    open_StubWithCallback(open_general_callback);
    ioctl_StubWithCallback(ioctl_general_callback);
    close_StubWithCallback(close_callback);

    ret = gpio_line_request(gpio_chip, line_flag, consumer, &test_gpio_line);

    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(16, test_gpio_line.fd); 
}

/*******************************************************************************
 *    gpio_get_line_event unit tests
 ******************************************************************************/

/*
 * Verify gpio_get_line_event() returns EBADF when called with an invalid file descriptor (-1).
 */
void test_gpio_get_line_event_invalid_fd_fail(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = -1,
        .state = false
    };
    
    enum gpio_v2_line_event_id line_event;
    read_StubWithCallback(read_falling_callback);
    ret = gpio_get_line_event(&test_gpio_line, &line_event);

    TEST_ASSERT_EQUAL_INT(EBADF, ret);
}


/*
 * Verify gpio_get_line_event() returns EBADE when read operation does not return a complete event structure.
 */
void test_gpio_get_line_event_incomplete_read_fail(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = false
    };

    enum gpio_v2_line_event_id line_event;
    read_StubWithCallback(read_incomplete_callback);
    ret = gpio_get_line_event(&test_gpio_line, &line_event);

    TEST_ASSERT_EQUAL_INT(EBADE, ret);
}

/*
 * Verify gpio_get_line_event() returns EINVAL when an unknown event ID is received.
 */
void test_gpio_get_line_event_unknown_event_fail(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = false
    };

    enum gpio_v2_line_event_id line_event;
    read_StubWithCallback(read_unknown_event_callback);
    ret = gpio_get_line_event(&test_gpio_line, &line_event);

    TEST_ASSERT_EQUAL_INT(EINVAL, ret);
}

/*
 * Verify gpio_get_line_event() successfully detects a rising edge event and returns the correct event ID.
 */
void test_gpio_get_line_event_rising_valid_success(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = false
    };

    enum gpio_v2_line_event_id line_event;
    read_StubWithCallback(read_rising_callback);
    ret = gpio_get_line_event(&test_gpio_line, &line_event);

    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(GPIO_V2_LINE_EVENT_RISING_EDGE, line_event); 

}


/*
 * Verify gpio_get_line_event() successfully detects a falling edge event and returns the correct event ID.
 */
void test_gpio_get_line_event_falling_valid_success(void)
{
    int ret = 0;

    struct gpio_line test_gpio_line = {
        .name = "test_gpio",
        .fd = 7,
        .state = false
    };

    enum gpio_v2_line_event_id line_event;
    read_StubWithCallback(read_falling_callback);
    ret = gpio_get_line_event(&test_gpio_line, &line_event);
    
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(GPIO_V2_LINE_EVENT_FALLING_EDGE, line_event); 

}
