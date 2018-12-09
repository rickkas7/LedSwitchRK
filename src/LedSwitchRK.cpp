
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

