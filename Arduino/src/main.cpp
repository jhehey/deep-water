#include <Arduino.h>
#include <string.h>
#include <neotimer.h>
#include "Level.h"
#include "Fuzzifier.h"
#include "RulesEngine.h"
#include "WireAdapter.h"
#include "DHT22Adapter.h"
#include "DS18B20Adapter.h"
#include "PHAdapter.h"

Neotimer timer = Neotimer(1000); // every 1 second

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);

	Serial.println("Arduino Setup Started");

	SetupWireAdapter();
	SetupPHSensor();
	SetupDHT22Sensor();
	SetupDS18B20Sensor();
}

void loop() {
  // put your main code here, to run repeatedly:

	if(timer.repeat())
	{
		// ReadSensors;
		float rawPh = ReadPH();
		float rawAir = ReadAirTempCelsius();
		float rawWater = ReadWaterTempCelsius();

		Level ph = GetPHLevel(rawPh);
		Level air = GetAirTempLevel(rawAir);
		Level water = GetWaterTempLevel(rawWater);

		bool rule1 = InferRule1(ph, air, water);
		bool rule2 = InferRule2(ph, air, water);
		bool rule3 = InferRule3(ph, air, water);
		bool alert = rule1 || rule2 || rule3;

		// Send Message
		// ph,air,water,phLevel,airLevel,waterLevel,alert
		String message = String(rawPh) + ',' +
			String(rawAir) + ',' +
			String(rawWater) + ',' +
			String(ph) + ',' +
			String(air) + ',' +
			String(water) + ',' +
			String(alert);


		Serial.print("pH: ");
		Serial.print(rawPh);
		Serial.print(" - ");
		Serial.print(LevelToString(ph));

		Serial.print(" | Air: ");
		Serial.print(rawAir);
		Serial.print(" - ");
		Serial.print(LevelToString(air));

		Serial.print(" | Water: ");
		Serial.print(rawWater);
		Serial.print(" - ");
		Serial.print(LevelToString(water));

		Serial.print(" | Rules: ");
		Serial.print(rule1);
		Serial.print(", ");
		Serial.print(rule2);
		Serial.print(", ");
		Serial.print(rule3);

		Serial.print(" | Alert: ");
		Serial.print(alert);
		Serial.print(" | ");

		Serial.println("Message sent to NodeMCU");
		WriteToWifi(message);
		// Serial.println(message);
	}
}
