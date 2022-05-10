#include <Arduino.h>
#include "WireAdapter.h"
#include "ThingSpeakAdapter.h"
#include "secrets.h"

#define POLLING_INTERVAL_MS 20000 // 20 seconds

const char *nodeName = NODE_NAME;

void ReceiveData();

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);

	Serial.println("NodeMCU Setup");

	SetupWireAdapter();
	SetupThingSpeak();
}

void loop() {
  // put your main code here, to run repeatedly:
	ReceiveData();
}

String data[9];


String LevelToString(int level) {
	switch(level) {
		case 0: return "LOW";
		case 1: return "NORMAL";
		case 2: return "HIGH";
		default: return "UNKNOWN";
	}
}

void ReceiveData()
{
	Wire.requestFrom(ADDR_MAIN, MAX_I2C_BUFFER_SIZE); /* request & read data of size 13 from slave */
	String ssData = "";

	while(Wire.available()){
		char c = (char) Wire.read();
		if(isAscii(c) && !isControl(c)) {
			ssData += c;
		}
	}
	ssData.trim();

	int length = ssData.length();

	if(length > 0) {
		// There is Data Received. Do Something with it
		// Serial.print("Length: ");
		// Serial.println(length);
		Serial.print("Received Data: ");
		Serial.println(ssData);

		const int dataCount = 7;
		float rawPh, rawAir, rawWater;
		int ph, air, water;
		int alert;

		if(sscanf(ssData.c_str(), "%f,%f,%f,%d,%d,%d,%d", 
		&rawPh, &rawAir, &rawWater,
		&ph, &air, &water, 
		&alert) == dataCount) {

			// Parsed Successfully. Ready to send to thingspeak
			SendThingSpeak(rawPh, rawAir, rawWater);

			// Send Email Alert
			if((bool) alert) {
				String name = String(nodeName);
				String subject = "ALERT! High Readings on " + name;
				String body = 
					"ph: " + LevelToString(ph) + " - " + String(rawPh) + "\\n" + 
					"Air Temperature: " + LevelToString(air) + " - " + String(rawAir) + "\\n" + 
					"Water Temperature: " + LevelToString(water) + " - " + String(rawWater) + "\\n";

				SendEmailAlert(subject, body);
				Serial.println(body);
			}
		}
	}

	delay(POLLING_INTERVAL_MS);
}
