#ifndef LORAGW_GPIO_H_
#define LORAGW_GPIO_H_

#include <stdint.h>
/** Initializes the requested GPIO pin and reads the value
@return Operation status
@param pin - pin to check
@param value - return value of the pin
@retval ERR_NO_ERROR  pin read
@retval ERR_UNSPECIFIED  Could not read
 */
int gpio_read_pin(uint16_t pin, uint8_t* value);

/** Initialize the requested GPIO pin and set in (direction)
@return Operation status
@param pin - pin to export
@retval ERR_NO_ERROR  pin initialized
@retval ERR_UNSPECIFIED  Could not export the pin
 */
int gpio_export_pin (uint16_t pin);

/** Set GPIO pin direction to (direction)
@return Operation status
@param pin - GPIO pin number to export
@param direction - 0=output, otherwise input
@retval (ERR_NO_ERROR)  Pin direction was set
@retval (ERR_UNSPECIFIED)  Could not set pin direction
*/
int gpio_set_direction(uint16_t pin, int direction);

/** Check whether GPIO is exported and available to use
@param pin - GPIO pin number to check
@retval true    GPIO exported
@retval false   GPIO NOT exported
 */
bool is_gpio_pin_exported(uint16_t pin);

/** Set the gpio rising edge
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_rising_edge(uint16_t pin);

/** Set the gpio falling edge
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_falling_edge(uint16_t pin);

/** Set the gpio active high
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_active_high(uint16_t pin);

/** Set the gpio active low
@param pin - GPIO pin number to change
@retval 0 - success, -1 - failed
 */
int gpio_set_active_low(uint16_t pin);

/** Open the file for the gpio pin
@param pin - GPIO pin number to change
@param flags - opening flags
@retval -1 - failed, otherwise file id
 */
int gpio_open_pin_fd(uint16_t pin, int flags);

#endif LORAGW_GPIO_H_
