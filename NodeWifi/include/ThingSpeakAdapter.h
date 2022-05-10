#ifndef __THINGSPEAKADAPTER_H__
#define __THINGSPEAKADAPTER_H__

#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

unsigned long myChannelNumber = SECRET_CH_ID;
const char *emailServer = SECRET_EMAIL_SERVER;
const char *myWriteAPIKey = SECRET_WRITE_APIKEY;
const char *myAlertAPIKey = SECRET_ALERT_APIKEY;
const char *ssid = SECRET_SSID;
const char *pass = SECRET_PASS;
const int wifiRetry = 30;
bool wifiConnected = false;

ESP8266WiFiMulti wiFiMulti;
WiFiClient  client;

void connectToWifi()
{
  int retryCount = 0;
  wiFiMulti.addAP(ssid, pass);
  Serial.print("Connecting to WIFI");
  while (wiFiMulti.run() != WL_CONNECTED)
  {
    Serial.print('.');
    if (retryCount >= wifiRetry)
    {
      retryCount = 0;
      Serial.println("Failed to connect to WIFI...");
      Serial.println("Retrying to connect to WIFI...");
    }
    delay(10);
  }
  Serial.println("\nSuccessfully connected to WIFI...");
  wifiConnected = true;
  delay(100); // small pause
}

void SetupThingSpeak(){
	connectToWifi();
  ThingSpeak.begin(client);

}

void SendThingSpeak(float ph, float air, float water) {
  // Write value to Field 1 of a ThingSpeak Channel
	ThingSpeak.setField(1, ph);
	ThingSpeak.setField(2, air);
	ThingSpeak.setField(3, water);
	int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }
}

void SendEmailAlert(const String& subject, const String& body)
{
	WiFiClientSecure newClient;
	newClient.setInsecure();

	HTTPClient emailClient;
	emailClient.begin(newClient, emailServer);
	emailClient.addHeader("Content-Type", "application/json");
	emailClient.addHeader("Thingspeak-Alerts-API-Key", myAlertAPIKey);

	String postStr = "{\"subject\":\"" + subject + "\",\"body\":\"" + body + "\"}";
	Serial.println(postStr);

	int responseCode = emailClient.POST(postStr);

	Serial.print(responseCode);
	Serial.print(" ");
	Serial.println(emailServer);

	emailClient.end();
}

#endif
