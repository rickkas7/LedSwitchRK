#include "Particle.h"

#include "LedSwitchRK.h"

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler;

LedSwitch ledSwitch(D5, D6); // led, switch
int lastRes = 0;

void setup() {
}

void loop() {
	int res = ledSwitch.pressed2();
	switch(res) {
	case LedSwitch::PRESSED_NOT:
		if (lastRes != res) {
			Log.info("PRESSED_NOT");
		}
		break;

	case LedSwitch::PRESSED_START:
		Log.info("PRESSED_START");
		break;

	case LedSwitch::PRESSED_1:
		Log.info("PRESSED_1");
		break;

	case LedSwitch::PRESSED_2:
		Log.info("PRESSED_2");
		break;

	case LedSwitch::PRESSED_3:
		Log.info("PRESSED_3");
		break;

	case LedSwitch::PRESSED_LONG_STARTED:
		Log.info("PRESSED_LONG_STARTED");
		break;

	case LedSwitch::PRESSED_LONG:
		Log.info("PRESSED_LONG");
		break;

	case LedSwitch::PRESSED_VERY_LONG:
		Log.info("PRESSED_VERY_LONG");
		break;

	case LedSwitch::PRESSED_IN_PROGRESS:
		if (lastRes != res) {
			Log.info("PRESSED_IN_PROGRESS");
		}
		break;

	}
	lastRes = res;
}

