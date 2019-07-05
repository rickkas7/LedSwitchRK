
#include "LedSwitchRK.h"

LedSwitch::LedSwitch(uint16_t ledPin, uint16_t switchPin) : ledPin(ledPin), switchPin(switchPin) {

	debounce.attach(switchPin, INPUT_PULLUP);
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
}

LedSwitch::~LedSwitch() {
}

void LedSwitch::ledOn() {
	ledState = true;
	digitalWrite(ledPin, ledState);
}

void LedSwitch::ledOff() {
	ledState = false;
	digitalWrite(ledPin, ledState);
}

void LedSwitch::ledToggle() {
	ledState = !ledState;
	digitalWrite(ledPin, ledState);
}

bool LedSwitch::pressed() {
	return debounce.update() && debounce.fell();
}


int LedSwitch::pressed2() {
	bool updated = debounce.update();

	switch(state) {
	case PRESSED_NOT:
		if (updated) {
			if (debounce.fell()) {
				state = PRESSED_1;
				lastFell = millis();
				lastRose = 0;
				return PRESSED_START;
			}
		}
		else {
			return PRESSED_NOT;
		}
		break;

	case PRESSED_1:
	case PRESSED_2:
	case PRESSED_3:
		if (updated) {
			if (debounce.rose()) {
				lastFell = 0;
				lastRose = millis();
				state++;
			}
		}
		else {
			if (lastFell && millis() - lastFell >= PRESSED_LONG_MS) {
				state = PRESSED_LONG;
				return PRESSED_LONG_STARTED;
			}
		}
		break;

	case PRESSED_1_WAIT:
	case PRESSED_2_WAIT:
	case PRESSED_3_WAIT:
		if (updated) {
			if (debounce.fell()) {
				lastFell = millis();
				lastRose = 0;
				state++;
			}
		}
		else {
			if (lastRose && millis() - lastRose >= INTER_TAP_MAX_MS) {
				// The inter-tap delay has been exceeded so we know whether we have
				// a single, double, or triple tap
				int result = state - 1;
				lastRose = 0;
				state = PRESSED_NOT;
				return result;
			}
		}
		break;

	case PRESSED_LONG:
		if (updated && debounce.rose()) {
			lastFell = lastRose = 0;
			state = PRESSED_NOT;
			return PRESSED_LONG;
		}
		else {
			if (millis() - lastFell >= PRESSED_VERY_LONG_MS) {
				state = PRESSED_VERY_LONG;
				return PRESSED_VERY_LONG;
			}
		}
		break;

	case PRESSED_VERY_LONG:
		if (updated && debounce.rose()) {
			lastFell = lastRose = 0;
			state = PRESSED_NOT;
			return PRESSED_NOT;
		}
		break;

	}
	return PRESSED_IN_PROGRESS;
}


	/*
	 * 	const int PRESSED_NOT = 0; // not being pressed
	const int PRESSED_START = 1; // starting to be pressed, equivalent to the result from pressed()
	const int PRESSED_1 = 2; // single tap. Only issued if not a double or triple tap, so there's a short delay before this is returned.
	const int PRESSED_2 = 3; // double tap
	const int PRESSED_3 = 4; // triple tap
	const int PRESSED_LONG_STARTED = 5; // long press (3 seconds) started (but could be long or very long)
	const int PRESSED_LONG = 6; // long press (3 seconds) and released before PRESSED_VERY_LONG
	const int PRESSED_VERY_LONG = 7; // very long press (10 seconds)
	 */


