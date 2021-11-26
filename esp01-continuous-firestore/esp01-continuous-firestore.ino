#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include "src/requestHandler/requestHandler.h"
#include "src/login/login.h"
#include "src/read_data/read_data.h"
#include "src/calcFlightTime/calcFligthTime.h"
#include "src/credentials/credentials.h"
#include "src/writeData/writeFlightTimeOnFirestore.h"

WiFiClient wifiClient;

#define RELAY 0

//const char *ssid = "BRONQUINHA";
//const char *password = "jrspcmcs03";

const int port = 443;
const String host = "home-dbb7e.rj.r.appspot.com";

const String loginHost = "identitytoolkit.googleapis.com";
const String path = "/v1/accounts:signInWithPassword?key=AIzaSyAIdWnqjoG0uo3Z2CYYpB0IHig1CqtLpKA";

//SHA-1 Fingerprint
const char fingerprintIdentityToolKit[] PROGMEM = "68 DB 23 67 82 7A 3D 3A 3D 68 E1 7B DD 8E 49 36 FB 46 8B B8";
const char fingerprintFirestore[] PROGMEM = "46 65 29 45 00 73 43 B9 68 B2 B9 47 9D 4B FD 21 19 C8 EF CF";
const String pathFlightTime = "/v1/projects/home-dbb7e/databases/(default)/documents/unities/rft43A10RZ4LOmMQ6gry/sections/Y2OksEM7ErCqr2jx8UQJ/devices/xC8UGLSYT8z2pxwKaAeY/flightTime";

const int delayBetweenReads = 230;

String body = "";
String token = "";
String currentToken = "";

WiFiClientSecure httpsClient;

void checkWifi()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void setup()
{
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  Serial.begin(115200); // must be same baudrate with the Serial Monitor
  httpsClient.setFingerprint(fingerprintIdentityToolKit);
  httpsClient.setTimeout(500);

  Serial.print("\n\n");
  Serial.print("Connecting to ");
  Serial.println(wifiSSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSSID, wifiPassword);

  checkWifi();

  // Print the IP address
  Serial.print("Ip address: ");
  Serial.print(WiFi.localIP());
}

void loop()
{
  unsigned long now = millis();
  if (currentToken == "")
    currentToken = loginFirestoreWithEmail(emailFirebase, passwordFirebase, loginHost, path, fingerprintIdentityToolKit);
  if (currentToken == "")
    return;
  const String value = readFromFirestore("firestore.googleapis.com", "/v1/projects/home-dbb7e/databases/(default)/documents/unities/rft43A10RZ4LOmMQ6gry/sections/Y2OksEM7ErCqr2jx8UQJ/devices/xC8UGLSYT8z2pxwKaAeY", currentToken, fingerprintFirestore);
  if (value == "")
  {
    currentToken = "";
    return;
  }
  if (value == "on")
  {
    digitalWrite(RELAY, LOW);
  }
  else
  {
    digitalWrite(RELAY, HIGH);
  }
  unsigned long flight = getFlightTime(now);

  writeFlightTimeOnFirestore("firestore.googleapis.com", pathFlightTime, String(flight), currentToken, fingerprintFirestore);
  Serial.println("value: " + value);

  if (flight > delayBetweenReads)
  {
    return;
  }
  delay(delayBetweenReads - flight);
}
