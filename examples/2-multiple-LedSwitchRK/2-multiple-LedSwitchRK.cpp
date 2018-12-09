#include "Particle.h"

#include "LedSwitchRK.h"

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler;

LedSwitch switches[4] = {
		// { LED pin, switch pin }
		LedSwitch(D5, D6),
		LedSwitch(A3, A2),
		LedSwitch(D3, D4),
		LedSwitch(A1, A0)
};


void setup() {
}

void loop() {

	for(size_t ii = 0; ii < (sizeof(switches) / sizeof(switches[0])); ii++) {
		if (switches[ii].pressed()) {
			switches[ii].ledToggle();
		}
	}
}
