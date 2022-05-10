#ifndef __PHADAPTER_H__
#define __PHADAPTER_H__

#include <Arduino.h>

void SetupPHSensor() {
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	digitalWrite(6, LOW);
	digitalWrite(7, HIGH);
}


float ReadPH()
{
	// Adjust value
	float calibrationFactor = 3.3;

	int rawPh = analogRead(A0);
	float ph = (float) rawPh * 5.0 / 1024;
	float phValue = calibrationFactor*ph;
	return phValue;
}


#endif
