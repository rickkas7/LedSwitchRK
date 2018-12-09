#include "Particle.h"

#include "LedSwitchRK.h"

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler;

LedSwitch ledSwitch(D4, D5); // led, switch

void setup() {
}

void loop() {
	if (ledSwitch.pressed()) {
		ledSwitch.ledToggle();
	}
}
