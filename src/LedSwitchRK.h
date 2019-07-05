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
	 *
	 * You should use either pressed() or pressed2(), but not both as they'll conflict with each other.
	 */
	bool pressed();

	/**
	 * @brief Alternative to pressed() that can return other options
	 *
	 * You should call pressed2() on every iteration of loop() and check the result code. The exact
	 * codes and their semantics are listed below, but most typically you'll be interested in:
	 *
	 * - PRESSED_1 single-tap
	 * - PRESSED_2 double-tap
	 * - PRESSED_3 triple-tap
	 * - PRESSED_LONG long press (3 seconds)
	 * - PRESSED_VERY_LONG very long press (10 seconds)
	 *
	 * You should use either pressed() or pressed2(), but not both as they'll conflict with each other.
	 */
	int pressed2();

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

	// Return codes from pressed2();

	/**
	 * @brief Returned by pressed2() when the button is not being pressed.
	 */
	static const int PRESSED_NOT = 0;

	/**
	 * @brief Returned by pressed2() when the button is starting to be pressed.
	 *
	 * This is equivalent to true from pressed(). At this point we don't know whether it will a single tap,
	 * double tap, long press, etc.. It will be returned as soon as the button is pressed. The other codes
	 * like PRESSED_1, PRESSED_2 (double tap), PRESSED_3, PRESSED_LONG are only returned after the button
	 * is released, and sometimes with an additional delay. This return code is used if you want an immediate
	 * action as soon as the button is pressed, and you may augment this action with PRESSED_2, etc. later.
	 */
	static const int PRESSED_START = 1;

	/**
	 * @brief Returned by pressed2() when the button is single tapped.
	 *
	 * This is returned approximately 500 milliseconds after the button is released, when we know for sure
	 * it's not a multi-tap or long press. On a double-tap, triple-tap or long press you will not see this
	 * return code, only the correct code is returned.
	 */
	static const int PRESSED_1 = 2;

	/**
	 * @brief This code is never returned; it's used internally by the button handling state machine.
	 */
	static const int PRESSED_1_WAIT = 3;

	/**
	 * @brief Returned by pressed2() when the button is double tapped.
	 *
	 * This is returned approximately 500 milliseconds after the button is released, when we know for sure
	 * it's not a multi-tap or long press. On a triple-tap or long press you will not see this
	 * return code, only the correct code is returned. You also will not see PRESSED_1 on double-tap.
	 */
	static const int PRESSED_2 = 4;

	/**
	 * @brief This code is never returned; it's used internally by the button handling state machine.
	 */
	static const int PRESSED_2_WAIT = 5;

	/**
	 * @brief Returned by pressed2() when the button is triple tapped.
	 *
	 * This is returned approximately 500 milliseconds after the button is released, when we know for sure
	 * it's not a multi-tap or long press. On a double-tap, triple-tap or long press you will not see this
	 * return code, only the correct code is returned. You also will not see PRESSED_1 on triple-tap.
	 */
	static const int PRESSED_3 = 6; // triple tap

	/**
	 * @brief This code is never returned; it's used internally by the button handling state machine.
	 */
	static const int PRESSED_3_WAIT = 7;

	/**
	 * @brief Returned by pressed2() when the button has been held down long enough for a long press
	 *
	 * This is an in-progress result. Either PRESSED_LONG or PRESSED_VERY_LONG will be returned.
	 */
	static const int PRESSED_LONG_STARTED = 8;

	/**
	 * @brief Returned by pressed2() when the button has been long pressed (> 3 seconds) but less than very long pressed (> 10 seconds)
	 *
	 * It is only returned after the button is released; if you only want to know if the long press has been started
	 * and do not care about PRESSED_VERY_LONG you can use PRESSED_LONG_STARTED instead.
	 */
	static const int PRESSED_LONG = 9;

	/**
	 * @brief Returned by pressed2() when the button has been very long pressed (> 10 seconds)
	 *
	 * This is returned while the button is still being pressed, it does not require a release.
	 */
	static const int PRESSED_VERY_LONG = 10;

	/**
	 * @brief Returned by pressed() when a button press is in progress but we don't know what the final result will be yet
	 */
	static const int PRESSED_IN_PROGRESS = 11;

	/**
	 * @brief After the button is released, the amount of time in milliseconds allowed for the next press to be a multi-press.
	 *
	 * The problem of making this long is that PRESSED_1, PRESSED_2, and PRESSED_3 won't be returned until this many
	 * milliseconds after button release. Making it shorter reduces the latency but makes it harder to multi-press.
	 */
	static const unsigned long INTER_TAP_MAX_MS = 500;

	/**
	 * @brief Number of milliseconds to register a long press (3 seconds).
	 */
	static const unsigned long PRESSED_LONG_MS = 3000;

	/**
	 * @brief Number of milliseconds to register a very long press (10 seconds).
	 */
	static const unsigned long PRESSED_VERY_LONG_MS = 10000;

protected:
	uint16_t ledPin;
	uint16_t switchPin;
	bool ledState = false;
	Debounce debounce;
	unsigned long lastFell = 0;
	unsigned long lastRose = 0;
	int state = PRESSED_NOT;
};

#endif /* __LEDSWITCHRK_H */
