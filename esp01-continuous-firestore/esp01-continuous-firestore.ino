#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include "src/requestHandler/requestHandler.h"
#include "src/login/login.h"
#include "src/read_data/read_data.h"

WiFiClient wifiClient;

#define RELAY 0

const char *ssid = "Ric Net";
const char *password = "jrspcmcs03";
//const char *ssid = "BRONQUINHA";
//const char *password = "jrspcmcs03";

const String email = "raphaeldesouza@outlook.com";
const String emailPassword = "123456";

const int port = 443;

String ip = "";
String mac = "60:01:94:21:E7:FA";
const char *host = "home-dbb7e.rj.r.appspot.com";

const String loginHost = "identitytoolkit.googleapis.com";
const String path = "/v1/accounts:signInWithPassword?key=AIzaSyAIdWnqjoG0uo3Z2CYYpB0IHig1CqtLpKA";

//SHA-1 Fingerprint
const char fingerprint[] PROGMEM = "68 DB 23 67 82 7A 3D 3A 3D 68 E1 7B DD 8E 49 36 FB 46 8B B8";
const char fingerprintFirestore[] PROGMEM = "46 65 29 45 00 73 43 B9 68 B2 B9 47 9D 4B FD 21 19 C8 EF CF";


const int delayBetweenReads = 5000;

bool ok = false;

String body = "";
String token = "";
int statusCode = -1;

bool done = false;

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
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(500);

  Serial.print("\n\n");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  checkWifi();

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  ip = WiFi.localIP().toString();
  //  mac = WiFi.macAddress();
  Serial.println(ip);
}

String currentToken = "";
void loop()
{
  if (done)
  {
    return;
  }
  if (currentToken == "")
    currentToken = loginFirestoreWithEmail(email, emailPassword, loginHost, path, fingerprint);
  if (currentToken == "")
    return;
  const String state = readFromFirestore("firestore.googleapis.com","/v1/projects/home-dbb7e/databases/(default)/documents/unities/rft43A10RZ4LOmMQ6gry/sections/Y2OksEM7ErCqr2jx8UQJ/devices/xC8UGLSYT8z2pxwKaAeY", currentToken, fingerprintFirestore);
  Serial.println("state: " + state);
  Serial.println(".");

  delay(delayBetweenReads);
}
