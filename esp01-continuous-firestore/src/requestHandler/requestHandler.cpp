#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "requestHandler.h"

WiFiClientSecure requestClient;
bool makeRequest(String url, String path, String body, const String headers, String requesType, int port, const char *fingerprint)
{
  requestClient.setFingerprint(fingerprint);
  requestClient.setTimeout(500);
  Serial.println("Connecting to " + url + ":" + port);
  if (!requestClient.connect(url, port))
  {
    Serial.println("Connection on request failed.");
    return false;
  }

  Serial.println("Sending " + requesType);
  requestClient.print(String(requesType + " ") + path + " HTTP/1.1\r\n" +
                      "Host: " + url + "\r\n" +
                      "Content-Type: application/json" + headers +
                      "Connection: close\n" +
                      "Content-Length: " + body.length() +
                      "\n\n" +
                      body + "\n");
  // "\r\n\r\n"
  Serial.println("request sent");

  return true;
}

Request postRequest(String url, String path, String body, const char *fingerprint)
{
  bool result = makeRequest(url, path, body, "", "POST", 443, fingerprint);
  if (!result)
  {
    Serial.println("Request post failed.");
    Request error = {400, "Bad Request"};
    return error;
  }
  String responseBody = readBody();
  Request request = {200, responseBody};
  return request;
}

Request getRequest(String url, String path, const String headers, const char* fingerprint)
{
  bool result = makeRequest(url, path, "", headers, "GET", 443, fingerprint);
  if (!result)
  {
    Serial.println("Request get failed.");
    Request error = {400, "Bad Request"};
    return error;
  }
  String responseBody = readBody();
  Request request = {200, responseBody};
  return request;
}

String readBody()
{
  String requestBody = "";
  String line;
  while (requestClient.connected())
  {
    line = requestClient.readStringUntil('\n');
    if (line == "\r")
    {
      // Serial.println(line);
      // Serial.println("headers received");
      break;
    }
    else
    {
      // Serial.print(line);
    }
  }

  String last = "";
  String penultimate = "";
  bool first = true;

  while (requestClient.available())
  {
    line = requestClient.readStringUntil('\n');
    if (first)
    {
      first = false;
    }
    else
    {
      // Serial.println(last + "|");
      requestBody = requestBody + penultimate;
      penultimate = last;
      last = line;
    }
  }
  return requestBody;
}
