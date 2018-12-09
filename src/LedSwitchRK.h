#ifndef __LEDSWITCHRK_H
#define __LEDSWITCHRK_H

// https://github.com/rickkas7/LedSwitchRK
// License: MIT

#include "Particle.h"

// Debounce library: https://github.com/dwcares/debounce
#include "Debounce.h"

/**
 * @brief Handy library for the SparkFun tactile switch with LED with debouncing
 *
 * Typically you instantiate one of these for each LED switch you have.
 */
class LedSwitch {
public:
	/**
	 * @brief Constructor. Takes the pin for the LED and the pin for the switch.
	 *
	 * @param ledPin The pin the LED is connected to (with a current-limiting resistor, of course). LED should be connected to this pin and GND.
	 * @param switchPin The pin the switch is connected to. This assumes the other side of the switch is connected to GND!
	 */
	LedSwitch(uint16_t ledPin, uint16_t switchPin);

	/**
	 * @brief Destructor
	 *
	 * Since you normally instantiate one of these as a global object it's not typically deleted.
	 */
	virtual ~LedSwitch();

	/**
	 * @brief Returns true if the button is pressed. You should call this on every loop()
	 *
	 * @return true if pressed, false if not. The output is debounced.
	 */
	bool pressed();

	/**
	 * @brief Turn the LED on
	 */
	void ledOn();

	/**
	 * @brief Turn the LED off
	 */
	void ledOff();

	/**
	 * @brief Toggle the LED (if it was on, turn it off, and vice versa).
	 */
	void ledToggle();

	/**
	 * @brief Get the pin the LED is connected to (that was passed to the constructor)
	 */
	inline uint16_t getLedPin() const { return ledPin; };

	/**
	 * @brief Get the pin the switch is connected to (that was passed to the constructor)
	 */
	inline uint16_t getSwitchPin() const { return switchPin; };

	/**
	 * @brief Gets the current LED state (true = on).
	 */
	inline bool getLedState() const { return ledState; };

protected:
	uint16_t ledPin;
	uint16_t switchPin;
	bool ledState = false;
	Debounce debounce;
};

#endif /* __LEDSWITCHRK_H */
