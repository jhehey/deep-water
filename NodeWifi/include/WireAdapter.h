#ifndef __WIREADAPTER_H__
#define __WIREADAPTER_H__

#include <Arduino.h>
#include <Wire.h>

#define ADDR_MAIN 1
#define ADDR_WIFI 6
#define MAX_I2C_BUFFER_SIZE 64

void writeToWire(String data, int address)
{
  Wire.beginTransmission(address);
  Wire.println(data);
  Wire.endTransmission();
}

void WriteToWifi(String data) {
	writeToWire(data, ADDR_WIFI);
}

void WriteToMain(String data) {
	writeToWire(data, ADDR_MAIN);
}

void SetupWireAdapter()
{
	Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */


  // Wire.begin(ADDR_WIFI);
  // Wire.onReceive(onWireReceive);
}

#endif
