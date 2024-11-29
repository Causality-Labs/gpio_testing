#include <stdio.h>
#include <stdint.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define GPIO_BASE_PATH "/dev/virt_gpio"

/** Initialize the requested GPIO pin and set in (direction)
@return Operation status
@param pin - pin to export
@retval ERR_NO_ERROR  pin initialized
@retval ERR_UNSPECIFIED  Could not export the pin
 */
/*
int gpio_export_pin (uint16_t pin)
{


}
*/

/** Check whether GPIO is exported and available to use
 * 
@param chip_fd - File descriptor of the GPIO chip
@param pin - GPIO pin number to check
@retval true    GPIO pin is on the chip
@retval false   GPIO pin is not on the chip
 */
bool is_gpio_pin_exported(int chip_fd, uint16_t pin)
{

    // TODO: Check gpio info and see if the gpio pin is availbale in virtual gpio chip.
    
    struct gpio_v2_line_info line_info;
    int ret = 0;
    memset(&line_info, 0, sizeof(line_info));
    line_info.offset = pin;

    ret = ioctl(chip_fd, GPIO_V2_GET_LINEINFO_IOCTL, &line_info);
    if (ret < 0)
    {	
        perror("Error getting gpio chip info error message is: ");
        return false;
    }

    return true;
}

#if 0
/** Open the file for the gpio pin
@param pin - GPIO pin number to change
@param flags - opening flags
@retval -1 - failed, otherwise file id
 */
int gpio_open_pin_fd(uint16_t pin, int flags)
{

}


/** Initializes the requested GPIO pin and reads the value
@return Operation status
@param pin - pin to check
@param value - return value of the pin
@retval ERR_NO_ERROR  pin read
@retval ERR_UNSPECIFIED  Could not read
 */
int gpio_read_pin(uint16_t pin, uint8_t* value)
{


}


/** Set GPIO pin direction to (direction)
@return Operation status
@param pin - GPIO pin number to export
@param direction - 0=output, otherwise input
@retval (ERR_NO_ERROR)  Pin direction was set
@retval (ERR_UNSPECIFIED)  Could not set pin direction
*/
int gpio_set_direction(uint16_t pin, int direction)
{


}

/** Set the gpio rising edge
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_rising_edge(uint16_t pin)
{

}

/** Set the gpio falling edge
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_falling_edge(uint16_t pin)
{

}

/** Set the gpio active high
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_active_high(uint16_t pin)
{

}

/** Set the gpio active low
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_active_low(uint16_t pin)
{

}
#endif

