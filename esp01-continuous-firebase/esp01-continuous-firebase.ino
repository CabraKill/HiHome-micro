#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

WiFiClient wifiClient;

#define RELAY 0

const char* ssid = "Ric Net";
const char* password = "jrspcmcs03";
//const char *ssid = "BRONQUINHA";
//const char *password = "jrspcmcs03";

const int port = 443;

String ip = "";
String mac = "60:01:94:21:E7:FA";
const char* host = "home-dbb7e.rj.r.appspot.com";
//SHA-1 Fingerprint
const char fingerprint[] PROGMEM = "31 B5 9C 32 CA EC 0B 29 DB 00 6F B7 29 9B BB F2 02 DF 0E 1C";

void setup()
{
  Serial.begin(115200); // must be same baudrate with the Serial Monitor

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  ip = WiFi.localIP().toString();
  //  mac = WiFi.macAddress();
}

void loop()
{
  delay(500);

  WiFiClientSecure httpsClient;
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(500);
  Serial.print("HTTPS Connecting");
  int r = 0; //retry counter
  if (!httpsClient.connect(host, port)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/homes/buHkimoPE1e5NMx7C4kX/devices/" + mac;
  httpsClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "Connection: close\r\n\r\n");
  Serial.println("request sent");

  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while (httpsClient.available()) {
    line = httpsClient.readStringUntil('\r');  //Read Line by Line
    Serial.println(line); //Print response
  }

  Serial.println("==========");
  if (line == "on") {
    digitalWrite(RELAY, LOW);
    Serial.println("on");
  } else if (line == "off") {
    digitalWrite(RELAY, HIGH);
    Serial.println("off");
  }
  Serial.println();
  Serial.println("closing connection");
}
