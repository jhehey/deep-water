#ifndef __WIREADAPTER_H__
#define __WIREADAPTER_H__

#include <Arduino.h>
#include <Wire.h>

#define ADDR_MAIN 1
#define ADDR_WIFI 6
#define MAX_I2C_BUFFER_SIZE 64

char buffer[MAX_I2C_BUFFER_SIZE];

void writeToWire(String data, int address)
{
  Wire.beginTransmission(address);
  Wire.println(data);
  Wire.endTransmission();
}

void WriteToWifi(String data) {
	data.toCharArray(buffer, MAX_I2C_BUFFER_SIZE);
	// writeToWire(data, ADDR_WIFI);
}

void WriteToMain(String data) {
	writeToWire(data, ADDR_MAIN);
}

void onWireRequest() {
	Wire.write(buffer);
}

void onWireReceive(int bytes)
{
  String ssData = "";
  while (Wire.available())
  {
    char c = (char)Wire.read();
    ssData += c;
  }

  ssData.trim();
  Serial.print("Received Data: ");
  Serial.println(ssData);
}

void SetupWireAdapter()
{
  Wire.begin(ADDR_MAIN);
  Wire.onReceive(onWireReceive);
	Wire.onRequest(onWireRequest);
}

#endif
